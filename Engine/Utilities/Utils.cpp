//
// Created by Vlad Boroday on 2023-12-12.
//

#include "Utils.h"

SEngine::String SEngine::GetAssetPath(const char* path)
{
#if defined(__linux__)
	String ResourcesFormat = "{}Resources/{}";
#else
	String ResourcesFormat = "{}/Resources/{}";
#endif
	return SEngine::Format(ResourcesFormat, GetApplicationDirectory(), path);
}

SEngine::String SEngine::GetAssetPath(const SEngine::String& path)
{
	return GetAssetPath(path.c_str());
}
float SEngine::TimeNowSeconds(const SEngine::Ecs::world& world)
{
	return world.get_info()->world_time_total;
}
