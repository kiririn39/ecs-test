//
// Created by Vlad Boroday on 2023-12-06.
//
#include "glm/gtc/random.hpp"

template<typename Number>
Number SEngine::Math::GetRandomValue(Number min, Number max)
{
	return glm::linearRand(min, max);
}

template<typename Number>
Number SEngine::Math::Clamp(Number value, Number min, Number max)
{
	return glm::clamp(value, min, max);
}
