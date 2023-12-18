//
// Created by Vlad Boroday on 2023-12-03.
//

#ifndef UNTITLED1_ENGINE_CORE_TYPES_H_
#define UNTITLED1_ENGINE_CORE_TYPES_H_

#include "Window.hpp"
#include "Engine/Types.h"

namespace SEngine
{
	struct Window
	{
		raylib::Window* WindowHandle;
	};
	struct MainWindow
	{
	};
	struct WindowSize
	{
		Vector2 Dimension;
	};
	struct WindowTitle
	{
		String Title;
	};

	struct MouseInput
	{
		Vector2 Position;
		Vector2 PositionDelta;
	};

	namespace RenderPhases
	{
		struct PreDraw
		{
		};
		struct Draw
		{
		};
		struct PostDraw
		{
		};
	};
}

#endif //UNTITLED1_ENGINE_CORE_TYPES_H_
