//
// Created by Vlad Boroday on 2023-11-26.
//

#ifndef CHESSGAME_SIMPLEENGINE_UTILITIES_FORMAT_H_
#define CHESSGAME_SIMPLEENGINE_UTILITIES_FORMAT_H_

#include "Engine/Core/Types.h"
#include "fmt/core.h"
#include "fmt/chrono.h"

namespace SEngine
{
	template<typename... Args>
	String Format(const flecs::string_view& formatStr, Args&& ... args)
	{
		return fmt::format(fmt::runtime(formatStr.c_str()), std::forward<Args>(args)...);
	}

	template<typename... Args>
	String Format(const String& formatStr, Args&& ... args)
	{
		return fmt::format(fmt::runtime(formatStr), std::forward<Args>(args)...);
	}
}

#endif //CHESSGAME_SIMPLEENGINE_UTILITIES_FORMAT_H_
