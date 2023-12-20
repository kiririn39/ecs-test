//
// Created by Vlad Boroday on 2023-12-06.
//

#include "Math.h"

bool SEngine::Math::IsCompletelyEnvelopsBox(
	SEngine::BoundingBox outer,
	SEngine::BoundingBox inner,
	SEngine::Vector3& overlap)
{
	overlap.x = glm::min(outer.max.x, inner.max.x) - glm::max(outer.min.x, inner.min.x);
	overlap.y = glm::min(outer.max.y, inner.max.y) - glm::max(outer.min.y, inner.min.y);
	overlap.z = glm::min(outer.max.z, inner.max.z) - glm::max(outer.min.z, inner.min.z);

	return overlap.x > 0 && overlap.y > 0 && overlap.z > 0;
}

bool SEngine::Math::IsCompletelyEnvelopsBox(
	SEngine::BoundingBox outer,
	SEngine::BoundingBox inner,
	SEngine::Vector2& overlap)
{
	bool isCompletelyEnveloped =
		outer.min.x <= inner.min.x && outer.max.x >= inner.max.x &&
			outer.min.y <= inner.min.y && outer.max.y >= inner.max.y;

	if (isCompletelyEnveloped)
	{
		overlap.x = 0.0f;
		overlap.y = 0.0f;
	}
	else
	{
		overlap.x = glm::min(outer.max.x, inner.max.x) - glm::max(outer.min.x, inner.min.x);
		overlap.y = glm::min(outer.max.y, inner.max.y) - glm::max(outer.min.y, inner.min.y);
	}

	return isCompletelyEnveloped;
}