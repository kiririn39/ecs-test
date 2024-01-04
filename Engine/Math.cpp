//
// Created by Vlad Boroday on 2023-12-06.
//

#include "Math.h"

using namespace SEngine;
using namespace SEngine::Math;

OverlapInfo SEngine::Math::IsCompletelyOverlapsBox(SEngine::BoundingBox center, SEngine::BoundingBox target)
{
	OverlapInfo overlap;

	overlap.IsLeftOutside = target.min.x < center.min.x;
	overlap.IsRightOutside = target.max.x > center.max.x;
	overlap.IsTopOutside = target.min.y < center.min.y;
	overlap.IsBottomOutside = target.max.y > center.max.y;

	overlap.OverlapsCompletely = !overlap.IsLeftOutside && !overlap.IsRightOutside &&
		!overlap.IsTopOutside && !overlap.IsBottomOutside;

	overlap.OverlapsPartialy = !overlap.IsLeftOutside || !overlap.IsRightOutside ||
		!overlap.IsTopOutside || !overlap.IsBottomOutside;

	return overlap;
}

float SEngine::Math::Sin(float value)
{
	return glm::sin(value);
}
