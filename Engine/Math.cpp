//
// Created by Vlad Boroday on 2023-12-06.
//

#include "raylib.h"
#include "Math.h"
#include "raymath.h"

int SEngine::Math::GetRandomValue(int min, int max)
{
	return ::GetRandomValue(min, max);
}

float SEngine::Math::GetRandomValue(float min, float max)
{
	return Remap((float)GetRandomValue(0, 1000), 0.0f, 1000.0f, min, max);
}

bool SEngine::Math::IsCompletelyEnvelopsBox(
	SEngine::BoundingBox outer,
	SEngine::BoundingBox inner,
	SEngine::Vector2& bounceOffDirection)
{
	if (outer.min.x > inner.min.x)
		bounceOffDirection.x += 1;
	if (outer.min.y > inner.min.y)
		bounceOffDirection.y += 1;
	if (outer.max.x < inner.max.x)
		bounceOffDirection.x -= 1;
	if (outer.max.y < inner.max.y)
		bounceOffDirection.y -= 1;

	bool result = outer.min.x <= inner.min.x &&
		outer.min.y <= inner.min.y &&
		outer.min.z <= inner.min.z &&
		outer.max.x >= inner.max.x &&
		outer.max.y >= inner.max.y &&
		outer.max.z >= inner.max.z;

	return result;
}
