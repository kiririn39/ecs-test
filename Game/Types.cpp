//
// Created by Vlad Boroday on 2023-12-04.
//

#include "Types.h"
#include "Engine/Utilities/Utils.h"

Game1::DestroyComponent::DestroyComponent(const SEngine::Ecs::world& world, float delay)
{
	AtWorldTime = SEngine::TimeNowSeconds(world) + delay;
}

SEngine::BoundingBox Game1::Collision::BoxCollider::GetBoundingBox(SEngine::Vector2 position) const
{
	SEngine::Vector2 extent = Dimensions / 2.0f;
	SEngine::Vector3 min(position.x - extent.x, position.y - extent.y, 0.0f);
	SEngine::Vector3 max(extent.x + position.x, extent.y + position.y, 0.0f);
	return { min, max };
}

const SEngine::Ecs::entity Game1::SpawnInfo::NullParent = SEngine::Ecs::entity::null();