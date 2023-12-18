#include "Engine/Core/RenderingFeature.h"
#include "Engine/Core/InputFeature.h"
#include "Game/Systems.h"

int main()
{
	using namespace SEngine;
	ecs_os_init();
	flecs::log::set_level(0);
	flecs::world world;

	std::vector features = {
		RenderingFeature::MakeHandle(),
		InputFeature::MakeHandle(),
		Game1::GameSystems::MakeHandle()
	};

	world.set<flecs::Rest>({});
	world.import<flecs::monitor>
	();

	LifecycleHandle::ProcessHandles(world, features);

	while (world.progress())
	{
	}

	return 0;
}
