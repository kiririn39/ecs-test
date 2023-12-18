//
// Created by Vlad Boroday on 2023-12-04.
//

#include "Types.h"

Game1::DestroyComponent::DestroyComponent(const SEngine::Ecs::world& world, float delay)
{
	AtWorldTime = world.get_info()->world_time_total + delay;
}

SEngine::BoundingBox Game1::Collision::BoxCollider::GetBoundingBox(SEngine::Vector2 position) const
{
	SEngine::Vector2 extent = Dimensions / 2.0f;
	SEngine::Vector3 min(position.x - extent.x, position.y - extent.y, 0.0f);
	SEngine::Vector3 max(extent.x + position.x, extent.y + position.y, 0.0f);
	return { min, max };
}