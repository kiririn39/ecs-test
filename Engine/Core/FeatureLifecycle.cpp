//
// Created by Vlad Boroday on 2023-12-03.
//

#include "FeatureLifecycle.h"

void SEngine::LifecycleHandle::ProcessHandles(flecs::world& world, std::vector<LifecycleHandle>& handles)
{
	for (LifecycleHandle& handle : handles)
	{
		handle.RegisterTypes(world);
		handle.RegisterSystem(world);
		handle.InitGlobals(world);
	}
}