//
// Created by Vlad Boroday on 2023-12-12.
//

#include "Utils.h"

SEngine::String SEngine::GetAssetPath(const char* path)
{
	return SEngine::Format("{}/Resources/{}", GetApplicationDirectory(), path);
}

SEngine::String SEngine::GetAssetPath(const SEngine::String& path)
{
	return GetAssetPath(path.c_str());
}
