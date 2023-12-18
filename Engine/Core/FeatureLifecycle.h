//
// Created by Vlad Boroday on 2023-12-03.
//

#ifndef UNTITLED1_ENGINE_CORE_FEATURELIFECYCLE_H_
#define UNTITLED1_ENGINE_CORE_FEATURELIFECYCLE_H_

#include <functional>
#include <vector>
#include "Engine/ecs.h"

namespace SEngine
{
	struct LifecycleHandle
	{
		std::function<void(flecs::world & )> RegisterTypes;
		std::function<void(flecs::world & )> RegisterSystem;
		std::function<void(flecs::world & )> InitGlobals;

		static void ProcessHandles(flecs::world& world, std::vector<LifecycleHandle>& handles);
	};

	template<typename T>
	class FeatureLifecycle
	{
	 public:
		static LifecycleHandle MakeHandle()
		{
			return {
				T::RegisterTypes,
				T::RegisterSystem,
				T::InitGlobals
			};
		}

		static void RegisterTypes(flecs::world& world)
		{
		}

		static void RegisterSystem(flecs::world& world)
		{
		}

		static void InitGlobals(flecs::world& world)
		{
		}
	};
}

#endif //UNTITLED1_ENGINE_CORE_FEATURELIFECYCLE_H_
