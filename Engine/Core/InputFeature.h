//
// Created by Vlad Boroday on 2023-12-03.
//

#ifndef UNTITLED1_ENGINE_CORE_INPUTFEATURE_H_
#define UNTITLED1_ENGINE_CORE_INPUTFEATURE_H_

#include "FeatureLifecycle.h"
#include "Types.h"

namespace SEngine
{
	class InputFeature : public FeatureLifecycle<InputFeature>
	{
	 public:
		static void RegisterTypes(flecs::world& world);
		static void RegisterSystem(flecs::world& world);
		static void InitGlobals(flecs::world& world);
	 private:
		static void UpdateAxisChords(flecs::entity keyEntity, AxisChord& chord);
	};
}

#endif //UNTITLED1_ENGINE_CORE_INPUTFEATURE_H_
