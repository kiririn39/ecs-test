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

	struct OverlapInfo
	{
		bool IsTopOutside = false;
		bool IsBottomOutside = false;
		bool IsLeftOutside = false;
		bool IsRightOutside = false;

		bool OverlapsCompletely = false;
		bool OverlapsPartialy = false;
	};
	OverlapInfo IsCompletelyOverlapsBox(SEngine::BoundingBox center, SEngine::BoundingBox target);

	float Sin(float value);
}

#include "Math.inl"

#endif //UNTITLED1_ENGINE_MATH_H_
