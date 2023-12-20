//
// Created by Vlad Boroday on 2023-12-06.
//

#ifndef UNTITLED1_ENGINE_MATH_H_
#define UNTITLED1_ENGINE_MATH_H_

#include "Types.h"

namespace SEngine::Math
{
	template<typename Number>
	Number GetRandomValue(Number min, Number max);

	template<typename Number>
	Number Clamp(Number value, Number min, Number max);

	bool IsCompletelyEnvelopsBox(SEngine::BoundingBox outer,
		SEngine::BoundingBox inner,
		SEngine::Vector3& bounceOffDirection);

	bool IsCompletelyEnvelopsBox(SEngine::BoundingBox outer,
		SEngine::BoundingBox inner,
		SEngine::Vector2& bounceOffDirection);
}

#include "Math.inl"

#endif //UNTITLED1_ENGINE_MATH_H_
