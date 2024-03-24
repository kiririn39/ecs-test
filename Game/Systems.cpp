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
	SEngine::Ecs::entity shipBase;
	SEngine::Ecs::entity enemyPawnPrefab;

	SEngine::Ecs::query<const SEngine::Transform, const Collision::BoxCollider, Health> EnemiesQuery;

	void GameSystems::AddEnemyLineSpawn(SEngine::Ecs::world& world, SpawnInfo spawn,
			SEngine::Vector2 startAt, SEngine::Vector2 interval, int count)
	{
		for (int i = 0; i < count; ++i)
		{
			SEngine::Vector2 point = startAt + interval * i;

			spawn.Transform.Position.LocalPosition = point;
			world.entity().set<SpawnInfo>(spawn);
		}
	}

	void GameSystems::AddEnemyTriangleSpawn(SEngine::Ecs::world& world, SpawnInfo spawn,
			SEngine::Vector2 startAt, SEngine::Vector2 interval, int count)
	{
		int LineCount = 0;
		int LineIndex = 0;
		int LineSpawns = 1;

		for (int i = 0; i < count; ++i)
		{
			SEngine::Vector2 point =
					startAt + SEngine::Vector2(interval.x * LineIndex - interval.x * LineCount, interval.y * LineCount);

			spawn.Transform.Position.LocalPosition = point;
			world.entity().set<SpawnInfo>(spawn);

			LineIndex++;
			if (LineIndex >= LineSpawns)
			{
				LineIndex = 0;
				LineCount++;
				LineSpawns += 2;
			}
		}
	}

	void GameSystems::RegisterTypes(SEngine::Ecs::world& world)
	{
		onEnemyDied = world.entity("On enemy died event");

		EnemiesQuery = world.query_builder<const SEngine::Transform, const Collision::BoxCollider, Health>()
				.with<const Collision::EnemyLayer>()
				.build();
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

		auto enemiesSpawner = world.system("Spawn enemy spawns")
				.kind(SEngine::Ecs::PreFrame)
				.interval(5.0f)
				.iter([](SEngine::Ecs::iter iter)
				{
					flecs::world world = iter.world();

					SpawnInfo spawnInfo
							{
									.WorldTime = SEngine::TimeNowSeconds(world),
									.Transform.Rotation = SEngine::Rotation::Down,
									.Prefab = enemyPawnPrefab,
							};

					int count = SEngine::Math::GetRandomValue(2, 7);
					float xStart = SEngine::Math::GetRandomValue(50, 1000);
					AddEnemyLineSpawn(world, spawnInfo, { xStart, -100 }, { 100, -100 }, count);

					spawnInfo.WorldTime = SEngine::TimeNowSeconds(world) + 2.5f;
					count = SEngine::Math::GetRandomValue(5, 20);
					xStart = SEngine::Math::GetRandomValue(50, 1000);
					AddEnemyTriangleSpawn(world, spawnInfo, { xStart, -100 }, { 100, -100 }, count);
				});

		world.system<const SpawnInfo>("Spawn enemies from spawners")
				.kind(SEngine::Ecs::PreFrame)
				.interval(0.5f)
				.each([](SEngine::Ecs::entity entity, const SpawnInfo& spawnInfo)
				{
					if (SEngine::TimeNowSeconds(entity.world()) < spawnInfo.WorldTime)
						return;

					auto instance = entity.world().entity().set_doc_name("instance of enemy ship")
							.set<SEngine::Transform>({ spawnInfo.Transform })
							.is_a(spawnInfo.Prefab);

					if (spawnInfo.Parent != spawnInfo.NullParent)
						instance.child_of(spawnInfo.Parent);

					entity.set<DestroyComponent>({});
				}).depends_on(enemiesSpawner);

		world.system<SEngine::Transform, SEngine::KeyBinding>("Shoot lasers system")
				.term_at(1).with<Player>()
				.term_at(2).entity(SEngine::KeyBinding::Space_Key)
				.kind(SEngine::Ecs::OnUpdate)
				.interval(1 / 10.0f)
				.each([](const SEngine::Ecs::entity entity,
						const SEngine::Transform& transform,
						const SEngine::KeyBinding& keyBinding)
				{
					if (!keyBinding.IsKeyDown)
						return;

					entity.world().entity().is_a(beamPrefab)
							.set<SEngine::Transform>(transform)
							.set<DestroyComponent>({ entity.world(), 2.0f })
							.set_doc_name("instance of laser beam prefab");
				});

		world.system<Speed::Max, SEngine::Axis2D>("Move Entity by input")
				.term_at(2).entity(SEngine::Axis2D::MoveAxis2D)
				.with<ReceiveDirectionInput>()
				.kind(SEngine::Ecs::OnUpdate)
				.each([](SEngine::Ecs::entity entity,
						const Speed::Max& speed,
						const SEngine::Axis2D& axis)
				{
					entity.set<Velocity>({ axis.value * speed.Value });
				});

		world.system<SEngine::Transform, Speed::Max,
						Collision::BoxCollider, SEngine::CameraDimensions>(
						"Pawn ai system")
				.with<EnemyAi::Pawn>()
				.term_at(4).entity(SEngine::MainCamera)
				.kind(SEngine::Ecs::OnUpdate)
				.each([](SEngine::Ecs::entity entity,
						const SEngine::Transform& transform,
						const Speed::Max& MaxSpeed,
						const Collision::BoxCollider& collider,
						const SEngine::CameraDimensions& camera)
				{
					if (!entity.has<Velocity>())
					{
						entity.set<Velocity>({{ 0.0f, MaxSpeed.Value }});
					}
					else
					{
						Velocity* watever = entity.get_mut<Velocity>();

						watever->Value.y = MaxSpeed.Value;
					}

					auto entityBox = collider.GetBoundingBox(transform.Position.LocalPosition);
					auto overlap = SEngine::Math::IsCompletelyOverlapsBox(camera.AsBoundingBox(), entityBox);

					if (!overlap.OverlapsCompletely)
					{
						bool hitFloor = overlap.IsBottomOutside;

						if (hitFloor)
							entity.set<DestroyComponent>({ entity.world(), 0 });
					}
				});

		world.system<SEngine::Transform, SEngine::CameraDimensions>("Clamp player position to window size")
				.with<Player>()
				.term_at(2).entity(SEngine::MainCamera)
				.kind(SEngine::Ecs::PostUpdate)
				.each([](SEngine::Transform& transform, const SEngine::CameraDimensions& camera)
				{
					transform.Position.LocalPosition.x =
							SEngine::Math::Clamp(transform.Position.LocalPosition.x, 0.0f, camera.Value.x);
					transform.Position.LocalPosition.y =
							SEngine::Math::Clamp(transform.Position.LocalPosition.y, 0.0f, camera.Value.y);
				});

		world.system<SEngine::Transform, Velocity>("Apply velocity")
				.kind(SEngine::Ecs::PostUpdate)
				.each([](const SEngine::Ecs::entity entity, SEngine::Transform& transform, Velocity& velocity)
				{
					transform.Position.LocalPosition += velocity.Value * entity.world().delta_time();
				});

		world.system<SEngine::Transform, Collision::BoxCollider>(
						"Collide bullets with enemies system")
				.with<Collision::EnemyLayer, Collision::CollideWithLayer>()
				.kind(SEngine::Ecs::PostUpdate)
				.each([](SEngine::Ecs::iter iter,
						size_t i,
						const SEngine::Transform& transform,
						const Collision::BoxCollider& boxCollider)
				{
					SEngine::BoundingBox bulletBox = boxCollider.GetBoundingBox(transform.Position.LocalPosition);
					bool hasCollision = false;

					EnemiesQuery.each([bulletBox, &hasCollision](SEngine::Ecs::iter iter,
							size_t& index,
							const SEngine::Transform& transform,
							const Collision::BoxCollider& boxCollider,
							Health& health)
					{
						SEngine::BoundingBox box = boxCollider.GetBoundingBox(transform.Position.LocalPosition);
						hasCollision = box.CheckCollision(bulletBox);

						if (!hasCollision)
							return;

						iter.entity(index).set<Health>({ .Value = health.Value - 1 });

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

					for (auto& i: iter)
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
				.set<SEngine::Transform>({ .Position.LocalPosition = { dimensions.x / 2.0f, 50.0f }})
				.set<SEngine::TextComponent>({ .Text = { font.get<SEngine::FontCache>()->Id, "Score 0", 70.0f, 10.0f }})
				.set<ScoreCounter>({ .Format = "Score {}" });

		shipBase = world.prefab("ship prefab")
				.set<SEngine::Transform>({ .Position.LocalPosition = { 0, 0 }})
				.set<Collision::BoxCollider>({ .Dimensions = shipTexture.get<SEngine::TextureCache>()->Id.GetSize() })
				.set<Speed::Max>({ .Value = 200 })
				.set<SEngine::TextureComponent>({
						.Id = shipTexture.get<SEngine::TextureCache>()->Id,
						.DrawOrigin{ 0.5, 0.5 }});

		world.entity("instance of player ship")
				.add<Player>()
				.add<ReceiveDirectionInput>()
				.add<Collision::PlayerLayer>()
				.is_a(shipBase);

		beamPrefab = world.prefab("laser beam prefab")
				.set<Velocity>({ .Value = { 0, -300 }})
				.add<SEngine::Transform>()
				.add<DestroyComponent>()
				.add<Collision::EnemyLayer, Collision::CollideWithLayer>()
				.set<Collision::BoxCollider>({ .Dimensions = laserTexture.get<SEngine::TextureCache>()->Id.GetSize() })
				.set<SEngine::TextureComponent>({ .Id = laserTexture.get<SEngine::TextureCache>()->Id });

		enemyPawnPrefab = world.prefab().set_doc_name("enemy ship prefab")
				.add<SEngine::Transform>()
				.set<Speed::Max>({ .Value = 150 })
				.set<Health>({ .Value = 3 })
				.add<Collision::EnemyLayer>()
				.add<EnemyAi::Pawn>()
				.add<EnemyShip>()
				.is_a(shipBase);
	}
} // Game1
