//
// Created by Vlad Boroday on 2023-11-23.
//

#ifndef UNTITLED1_GAME_CORE_TYPES_H_
#define UNTITLED1_GAME_CORE_TYPES_H_

#include "memory"
#include "raylib-cpp.hpp"
#include "Game/Core/Time.h"

namespace SEngine
{
	template<typename T>
	using ObjectRef = std::weak_ptr<T>;

	typedef raylib::Vector2 Vector2;
	typedef raylib::Vector2 Vector2;
	typedef raylib::Vector3 Vector3;
	typedef raylib::Vector4 Vector4;

	typedef std::string String;
}

#endif //UNTITLED1_GAME_CORE_TYPES_H_
