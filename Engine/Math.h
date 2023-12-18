//
// Created by Vlad Boroday on 2023-12-06.
//

#ifndef UNTITLED1_ENGINE_MATH_H_
#define UNTITLED1_ENGINE_MATH_H_

#include "Types.h"
#include "mathfu/utilities.h"

namespace SEngine::Math
{
	using namespace mathfu;

	int GetRandomValue(int min, int max);
	float GetRandomValue(float min, float max);

	bool IsCompletelyEnvelopsBox(SEngine::BoundingBox outer,
		SEngine::BoundingBox inner,
		SEngine::Vector2& bounceOffDirection);
}

#endif //UNTITLED1_ENGINE_MATH_H_
