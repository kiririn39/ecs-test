//
// Created by Vlad Boroday on 2023-12-03.
//

#ifndef UNTITLED1_ENGINE_TYPES_H_
#define UNTITLED1_ENGINE_TYPES_H_

#include "ecs.h"
#include "raylib-cpp.hpp"

namespace SEngine
{
	using namespace raylib;

	typedef raylib::Vector2 Vector2;
	typedef raylib::Vector3 Vector3;
	typedef raylib::Vector4 Vector4;

	typedef std::string String;

	struct KeyBinding
	{
		KeyboardKey Key;

		// Check if a key has been pressed once
		bool IsKeyPressed;

		// Check if a key has been released once
		bool IsKeyReleased;

		// Check if a key is being pressed
		bool IsKeyDown;

		// Check if a key is NOT being pressed
		bool IsKeyUp;

		static Ecs::entity Space_Key;

		static Ecs::entity W_Key;
		static Ecs::entity S_Key;
		static Ecs::entity A_Key;
		static Ecs::entity D_Key;

		static Ecs::entity Up_Key;
		static Ecs::entity Down_Key;
		static Ecs::entity Left_Key;
		static Ecs::entity Right_Key;
	};

	struct Position
	{
		Vector2 LocalPosition;
	};

	struct Rotation
	{
		float Radians;

		const float GetAngle() const;
		void AddAngle(float angle);

		static Rotation CreateFromAngle(float angle);

		const static Rotation Up;
		const static Rotation Down;
		const static Rotation Left;
		const static Rotation Right;
	};

	struct Transform
	{
		Position Position;
		Rotation Rotation;
	};

	struct TextureComponent
	{
		SEngine::TextureUnmanaged Id;
		Vector2 DrawOrigin{ 0.5f, 0.5f };
	};

	struct TextComponent
	{
		SEngine::Text Text;
		Vector2 DrawOrigin{ 0.5f, 0.5f };
	};

	struct AxisChord
	{
		struct Positive
		{
		};
		struct Negative
		{
		};

		float Value = 0;

		static Ecs::entity MoveHorizontal;
		static Ecs::entity MoveVertical;
	};

	struct Axis2D
	{
		Vector2 value;

		struct Horizontal
		{
		};
		struct Vertical
		{
		};

		static Ecs::entity MoveAxis2D;
	};

	struct CameraDimensions
	{
		Vector2 Value;

		SEngine::BoundingBox AsBoundingBox() const;
	};

	struct TextureCache
	{
		SEngine::TextureUnmanaged Id;
	};

	struct FontCache
	{
		SEngine::Font Id;
	};
}

#endif //UNTITLED1_ENGINE_TYPES_H_
