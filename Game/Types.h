//
// Created by Vlad Boroday on 2023-12-04.
//

#ifndef UNTITLED1_GAME_COMPONENTS_TYPES_H_
#define UNTITLED1_GAME_COMPONENTS_TYPES_H_

#include "Engine/Types.h"

namespace Game1
{
	struct Player
	{
	};

	struct Velocity
	{
		SEngine::Vector2 Value;
	};

	struct Speed
	{
		struct Current
		{
			float Value;
		};

		struct Max
		{
			float Value;
		};
	};

	struct ReceiveDirectionInput
	{
	};

	struct DestroyComponent
	{
		float AtWorldTime;

		DestroyComponent() = default;

		DestroyComponent(const SEngine::Ecs::world& world, float delay);
	};

	struct Collision
	{
		struct BoxCollider
		{
			SEngine::Vector2 Dimensions;

			SEngine::BoundingBox GetBoundingBox(SEngine::Vector2 position) const;
		};

		struct PlayerLayer
		{
		};

		struct EnemyLayer
		{
		};

		struct ProjectilesLayer
		{
		};

		struct IgnoreLayer
		{

		};

		struct CollideWithLayer
		{
		};
	};

	struct Health
	{
		float MaxValue;
		float Value;
	};

	struct EnemyShip
	{

	};

	struct ScoreCounter
	{
		SEngine::String Format;
		float Value;
	};

	struct EnemyDied
	{

	};

	struct EnemyAi
	{
		struct Pawn
		{
		};
		struct Swarmer
		{
			
		};
	};

	struct SpawnInfo
	{
		float WorldTime = 0.0f;
		SEngine::Transform Transform;
		SEngine::Ecs::entity Prefab;
		SEngine::Ecs::entity Parent = SEngine::Ecs::entity::null();

		const static SEngine::Ecs::entity NullParent;
	};
}

#endif //UNTITLED1_GAME_COMPONENTS_TYPES_H_
