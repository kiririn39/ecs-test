//
// Created by Vlad Boroday on 2023-12-03.
//

#include "InputFeature.h"
#include "Engine/Utilities/Utils.h"
#include "Engine/GlobaEntities.h"

void SEngine::InputFeature::RegisterTypes(flecs::world& world)
{
	KeyBinding::Space_Key = world.entity("KEY_Space").set<KeyBinding>({ KeyboardKey::KEY_SPACE });

	KeyBinding::W_Key = world.entity("KEY_W").set<KeyBinding>({ KeyboardKey::KEY_W });
	KeyBinding::S_Key = world.entity("KEY_S").set<KeyBinding>({ KeyboardKey::KEY_S });
	KeyBinding::A_Key = world.entity("KEY_A").set<KeyBinding>({ KeyboardKey::KEY_A });
	KeyBinding::D_Key = world.entity("KEY_D").set<KeyBinding>({ KeyboardKey::KEY_D });

	KeyBinding::Up_Key = world.entity("KEY_UP").set<KeyBinding>({ KeyboardKey::KEY_UP });
	KeyBinding::Down_Key = world.entity("KEY_DOWN").set<KeyBinding>({ KeyboardKey::KEY_DOWN });
	KeyBinding::Left_Key = world.entity("KEY_LEFT").set<KeyBinding>({ KeyboardKey::KEY_LEFT });
	KeyBinding::Right_Key = world.entity("KEY_RIGHT").set<KeyBinding>({ KeyboardKey::KEY_RIGHT });

	AxisChord::MoveHorizontal = world.entity("Move horizontal")
		.add<AxisChord>()
		.add<AxisChord::Negative>(KeyBinding::A_Key)
		.add<AxisChord::Negative>(KeyBinding::Left_Key)
		.add<AxisChord::Positive>(KeyBinding::D_Key)
		.add<AxisChord::Positive>(KeyBinding::Right_Key);

	AxisChord::MoveVertical = world.entity("Move vertical")
		.add<AxisChord>()
		.add<AxisChord::Negative>(KeyBinding::W_Key)
		.add<AxisChord::Negative>(KeyBinding::Up_Key)
		.add<AxisChord::Positive>(KeyBinding::S_Key)
		.add<AxisChord::Positive>(KeyBinding::Down_Key);

	Axis2D::MoveAxis2D = world.entity("MoveAxis2D")
		.add<Axis2D>()
		.add<Axis2D::Horizontal>(AxisChord::MoveHorizontal)
		.add<Axis2D::Vertical>(AxisChord::MoveVertical);
}

void SEngine::InputFeature::InitGlobals(flecs::world& world)
{
}

void SEngine::InputFeature::RegisterSystem(flecs::world& world)
{
	flecs::entity updatekeysSystem = world.system<KeyBinding>("Update keys")
		.kind(flecs::PreFrame)
		.each([](KeyBinding& keyBinding)
		{
		  keyBinding.IsKeyDown = IsKeyDown(keyBinding.Key);
		  keyBinding.IsKeyUp = IsKeyUp(keyBinding.Key);
		  keyBinding.IsKeyPressed = IsKeyPressed(keyBinding.Key);
		  keyBinding.IsKeyReleased = IsKeyReleased(keyBinding.Key);
		});

	flecs::entity updateAxisSystem = world.system<AxisChord>("Update axis chords")
		.each(UpdateAxisChords)
		.depends_on(updatekeysSystem);

	world.system<Axis2D>()
		.with<Axis2D::Horizontal>(flecs::Wildcard).and_().with<Axis2D::Vertical>(flecs::Wildcard)
		.each([](flecs::entity entity, Axis2D& axis)
		{
		  flecs::entity horizontalEntity = entity.target<Axis2D::Horizontal>();
		  flecs::entity verticalEntity = entity.target<Axis2D::Vertical>();

		  axis.value.x = horizontalEntity.get<AxisChord>()->Value;
		  axis.value.y = verticalEntity.get<AxisChord>()->Value;
		})
		.depends_on(updateAxisSystem);
}

void SEngine::InputFeature::UpdateAxisChords(flecs::entity entity, AxisChord& chord)
{
	float direction = 0;

	entity.each<AxisChord::Positive>([&direction](flecs::entity keyEntity)
	{
	  const KeyBinding* key = keyEntity.get<KeyBinding>();

	  direction += IsKeyDown(key->Key);
	});
	entity.each<AxisChord::Negative>([&direction](flecs::entity keyEntity)
	{
	  const KeyBinding* key = keyEntity.get<KeyBinding>();

	  direction -= IsKeyDown(key->Key);
	});

	chord.Value = std::clamp(direction, -1.0f, 1.0f);
}