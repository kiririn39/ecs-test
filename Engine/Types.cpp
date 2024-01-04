//
// Created by Vlad Boroday on 2023-12-09.
//

#include "Types.h"
#include "ecs.h"
#include "Engine/Math.h"

flecs::entity SEngine::KeyBinding::Space_Key;

flecs::entity SEngine::KeyBinding::W_Key;
flecs::entity SEngine::KeyBinding::S_Key;
flecs::entity SEngine::KeyBinding::A_Key;
flecs::entity SEngine::KeyBinding::D_Key;

flecs::entity SEngine::KeyBinding::Up_Key;
flecs::entity SEngine::KeyBinding::Down_Key;
flecs::entity SEngine::KeyBinding::Left_Key;
flecs::entity SEngine::KeyBinding::Right_Key;

flecs::entity SEngine::AxisChord::MoveHorizontal;
flecs::entity SEngine::AxisChord::MoveVertical;

flecs::entity SEngine::Axis2D::MoveAxis2D;

SEngine::BoundingBox SEngine::CameraDimensions::AsBoundingBox() const
{
	return { Vector3::Zero(), Vector3(Value.x, Value.y, 0) };
}

const float SEngine::Rotation::GetAngle() const
{
	return SEngine::Math::Rad2Angle(Radians);
}

void SEngine::Rotation::AddAngle(float angle)
{
	Radians += SEngine::Math::Angle2Rad(Radians);
}

SEngine::Rotation SEngine::Rotation::CreateFromAngle(float angle)
{
	return SEngine::Rotation{ SEngine::Math::Angle2Rad(angle) };
}

const SEngine::Rotation SEngine::Rotation::Up = SEngine::Rotation::CreateFromAngle(0.0f);
const SEngine::Rotation SEngine::Rotation::Down = SEngine::Rotation::CreateFromAngle(180.0f);
const SEngine::Rotation SEngine::Rotation::Left = SEngine::Rotation::CreateFromAngle(270.0f);
const SEngine::Rotation SEngine::Rotation::Right = SEngine::Rotation::CreateFromAngle(90.0f);
