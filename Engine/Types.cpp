//
// Created by Vlad Boroday on 2023-12-09.
//

#include "Types.h"
#include "ecs.h"

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
