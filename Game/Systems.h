//
// Created by Vlad Boroday on 2023-12-04.
//

#ifndef UNTITLED1_GAME_SYSTEMS_H_
#define UNTITLED1_GAME_SYSTEMS_H_

#include "Engine/Core/FeatureLifecycle.h"
#include "Engine/Core/Types.h"
#include "Types.h"

namespace Game1
{

	class GameSystems : public SEngine::FeatureLifecycle<GameSystems>
	{
	 public:
		static void RegisterTypes(SEngine::Ecs::world& world);
		static void RegisterSystem(SEngine::Ecs::world& world);
		static void InitGlobals(SEngine::Ecs::world& world);

	 private:
		static void AddEnemyLineSpawn(SEngine::Ecs::world& world, SpawnInfo spawn,
			SEngine::Vector2 startAt, SEngine::Vector2 interval, int count);

		static void AddEnemyTriangleSpawn(SEngine::Ecs::world& world, SpawnInfo spawn,
			SEngine::Vector2 startAt, SEngine::Vector2 interval, int count);
	};

} // Game1

#endif //UNTITLED1_GAME_SYSTEMS_H_
