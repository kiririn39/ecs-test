//
// Created by Vlad Boroday on 2023-12-04.
//

#include "Systems.h"
#include "Engine/Types.h"
#include "Types.h"
#include "Engine/GlobaEntities.h"
#include "Engine/Math.h"
#include "Engine/Utilities/Utils.h"

namespace Game1
{
	SEngine::Ecs::entity shipTexture;
	SEngine::Ecs::entity laserTexture;
	SEngine::Ecs::entity font;
	SEngine::Ecs::entity beamPrefab;

	SEngine::Ecs::entity scoreText;
	SEngine::Ecs::entity onEnemyDied;

	SEngine::Ecs::query<const SEngine::Position, const Collision::BoxCollider, Health> EnemiesQuery;

	void GameSystems::RegisterTypes(SEngine::Ecs::world& world)
	{
		onEnemyDied = world.entity("On enemy died event");
	}

	void GameSystems::RegisterSystem(SEngine::Ecs::world& world)
	{
		auto scores = world.query_builder<ScoreCounter, SEngine::TextComponent>()
			.build();

		onEnemyDied.observe<EnemyDied>([scores]()
		{
		  scores.each([](ScoreCounter& score, SEngine::TextComponent& text)
		  {
			score.Value++;

			text.Text.text = SEngine::Format(score.Format, score.Value);
		  });
		});

		world.observer<SEngine::TextureCache>("TextureCache loader")
			.event(SEngine::Ecs::OnAdd)
			.each([](SEngine::Ecs::entity entity, SEngine::TextureCache& cache)
			{
			  SEngine::String path = SEngine::GetAssetPath(entity.name().c_str());
			  cache.Id = SEngine::TextureUnmanaged(path);
			});

		world.system<SEngine::Position, SEngine::KeyBinding>()
			.term_at(1).with<Player>()
			.term_at(2).entity(SEngine::KeyBinding::Space_Key)
			.kind(SEngine::Ecs::OnUpdate)
			.interval(1 / 30.0f)
			.each([](const SEngine::Ecs::entity entity,
				SEngine::Position& position,
				const SEngine::KeyBinding& keyBinding)
			{
			  if (!keyBinding.IsKeyDown)
				  return;

			  entity.world().entity().is_a(beamPrefab)
				  .set<SEngine::Position>(position)
				  .set<DestroyComponent>({ entity.world(), 2.0f })
				  .set_doc_name("instance of laser beam prefab");
			});

		world.system<Speed, SEngine::Position, SEngine::Axis2D>("Move Entity by input")
			.term_at(3).entity(SEngine::Axis2D::MoveAxis2D)
			.with<ReceiveDirectionInput>()
			.kind(SEngine::Ecs::OnUpdate)
			.each([](SEngine::Ecs::entity entity,
				const Speed& speed,
				const SEngine::Position& position,
				const SEngine::Axis2D& axis)
			{
			  entity.set<Velocity>({ axis.value * speed.Value });
			});

		world.system<SEngine::Position, Velocity, Collision::BoxCollider, SEngine::CameraDimensions>(
				"Oscillate enemy ships system")
			.with<EnemyShip>()
			.term_at(4).entity(SEngine::MainCamera)
			.kind(SEngine::Ecs::OnUpdate)
			.each([](SEngine::Ecs::entity entity,
				const SEngine::Position& position,
				Velocity& velocity,
				const Collision::BoxCollider& collider,
				const SEngine::CameraDimensions& camera)
			{
			  SEngine::Vector2 overlap;
			  auto entityBox = collider.GetBoundingBox(position.LocalPosition);
			  bool envelops = SEngine::Math::IsCompletelyEnvelopsBox(camera.AsBoundingBox(), entityBox, overlap);

			  if (!envelops)
			  {
				  if (overlap.x)
					  velocity.Value.x *= -1;
				  if (overlap.y)
					  velocity.Value.y *= -1;
			  }
			});

		world.system<SEngine::Position, SEngine::CameraDimensions>("Clamp player position to window size")
			.with<Player>()
			.term_at(2).entity(SEngine::MainCamera)
			.kind(SEngine::Ecs::PostUpdate)
			.each([](SEngine::Position& position, const SEngine::CameraDimensions& camera)
			{
			  position.LocalPosition.x = SEngine::Math::Clamp(position.LocalPosition.x, 0.0f, camera.Value.x);
			  position.LocalPosition.y = SEngine::Math::Clamp(position.LocalPosition.y, 0.0f, camera.Value.y);
			});

		world.system<SEngine::Position, Velocity>("Apply velocity")
			.kind(SEngine::Ecs::PostUpdate)
			.each([](const SEngine::Ecs::entity entity, SEngine::Position& position, Velocity& velocity)
			{
			  position.LocalPosition += velocity.Value * entity.world().delta_time();
			});

		EnemiesQuery = world.query_builder<const SEngine::Position, const Collision::BoxCollider, Health>()
			.with<const Collision::EnemyLayer>()
			.build();

		world.system<SEngine::Position, Collision::BoxCollider>(
				"Collide bullets with enemies system")
			.with<Collision::EnemyLayer, Collision::CollideWithLayer>()
			.kind(SEngine::Ecs::PostUpdate)
			.each([](SEngine::Ecs::iter iter,
				size_t i,
				const SEngine::Position& position,
				const Collision::BoxCollider& boxCollider)
			{
			  SEngine::BoundingBox bulletBox = boxCollider.GetBoundingBox(position.LocalPosition);
			  bool hasCollision = false;

			  EnemiesQuery.each([bulletBox, &hasCollision](SEngine::Ecs::iter iter,
				  size_t& index,
				  const SEngine::Position& position,
				  const Collision::BoxCollider& boxCollider,
				  Health& health)
			  {
				SEngine::BoundingBox box = boxCollider.GetBoundingBox(position.LocalPosition);
				hasCollision = box.CheckCollision(bulletBox);

				if (!hasCollision)
					return;

				health.Value -= 1;

				if (health.Value <= 0)
				{
					iter.entity(index).set<DestroyComponent>({ iter.world(), 0 });
					iter.entity(index).disable();

					onEnemyDied.emit<EnemyDied>();
				}

				index = iter.count();
			  });

			  if (!hasCollision)
				  return;

			  iter.entity(i).set<DestroyComponent>({ iter.world(), 0 });
			  iter.entity(i).disable();
			});

		world.system<DestroyComponent>("Destroy system")
			.with(SEngine::Ecs::Disabled).optional()
			.kind(SEngine::Ecs::PostUpdate)
			.iter([](SEngine::Ecs::iter iter, DestroyComponent* destroys)
			{
			  float worldTime = iter.world().get_info()->world_time_total;

			  for (auto& i : iter)
			  {
				  if (destroys[i].AtWorldTime <= worldTime)
					  iter.entity(i).destruct();
			  }
			});
	}

	void GameSystems::InitGlobals(SEngine::Ecs::world& world)
	{
		SEngine::Vector2 dimensions = SEngine::MainCamera.get<SEngine::CameraDimensions>()->Value;

		shipTexture = world.entity("SpaceShooterRedux/PNG/playerShip1_blue.png").add<SEngine::TextureCache>();
		laserTexture = world.entity("SpaceShooterRedux/PNG/Lasers/laserBlue07.png").add<SEngine::TextureCache>();
		font = world.entity("Fonts/insigne-display/Insigne Display.otf").add<SEngine::FontCache>();

		scoreText = world.entity("Score text")
			.set<SEngine::Position>({ .LocalPosition = { dimensions.x / 2.0f, 50.0f }})
			.set<SEngine::TextComponent>({ .Text = { font.get<SEngine::FontCache>()->Id, "Score 0", 70.0f, 10.0f }})
			.set<ScoreCounter>({ .Format = "Score {}" });

		SEngine::Ecs::entity shipBase = world.prefab("ship prefab")
			.set<SEngine::Position>({ .LocalPosition = { 0, 0 }})
			.set<Collision::BoxCollider>({ .Dimensions = shipTexture.get<SEngine::TextureCache>()->Id.GetSize() })
			.set<Speed>({ .Value = { 0, 0 }})
			.set<SEngine::TextureComponent>({
				.Id = shipTexture.get<SEngine::TextureCache>()->Id,
				.DrawOrigin{ 0.5, 0.5 }});

		world.entity("instance of player ship")
			.add<Player>()
			.set<Speed>({ .Value = { 100, 100 }})
			.add<ReceiveDirectionInput>()
			.add<Collision::PlayerLayer>()
			.is_a(shipBase);

		SEngine::Vector2 point((dimensions.x / 2), 50.0f);

		for (int i = 0; i < 1; ++i)
		{
			float xSpeed = SEngine::Math::GetRandomValue(-200.0f, 200.0f);
			point.y = SEngine::Math::GetRandomValue(50.0f, 400.0f);

			world.entity().set_doc_name("instance of enemy ship")
				.set<SEngine::Position>({ point })
				.set<Velocity>({ .Value = { xSpeed, 0 }})
				.set<Health>({ .Value = 10 })
				.add<Collision::EnemyLayer>()
				.add<EnemyShip>()
				.is_a(shipBase);
		}

		beamPrefab = world.prefab("laser beam prefab")
			.set<Velocity>({ .Value = { 0, -300 }})
			.add<SEngine::Position>()
			.add<DestroyComponent>()
			.add<Collision::EnemyLayer, Collision::CollideWithLayer>()
			.set<Collision::BoxCollider>({ .Dimensions = laserTexture.get<SEngine::TextureCache>()->Id.GetSize() })
			.set<SEngine::TextureComponent>({ .Id = laserTexture.get<SEngine::TextureCache>()->Id });
	}
} // Game1
