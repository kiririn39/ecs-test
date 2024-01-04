//
// Created by Vlad Boroday on 2023-12-03.
//

#ifndef UNTITLED1_ENGINE_CORE_RENDERINGFEATURE_H_
#define UNTITLED1_ENGINE_CORE_RENDERINGFEATURE_H_

#include "FeatureLifecycle.h"
#include "Types.h"

namespace SEngine
{
	class RenderingFeature : public FeatureLifecycle<RenderingFeature>
	{
	 public:
		static void RegisterTypes(flecs::world& world);
		static void RegisterSystem(flecs::world& world);
		static void InitGlobals(flecs::world& world);

	 private:
		static void WindowLifecycleHandler(flecs::iter& iter, Window* window);
		static void UpdateWindowTitle(flecs::iter& iter, const Window* window, const WindowTitle* title);
		static void UpdateWindowSize(SEngine::Window& window, const SEngine::WindowSize& size);
		static void CheckExitRequest(flecs::iter& iter, const Window* window);
		static void ReactToResize(flecs::iter& iter, const SEngine::Window* window, SEngine::WindowSize* Size);

		static void BeginDrawing(flecs::iter& iter, const Window* window);
		static void DrawTextureEntities(const SEngine::Transform& transform, const SEngine::TextureComponent& texture);
		static void DrawTextEntities(const SEngine::Transform& transform, const SEngine::TextComponent& textComponent);
		static void EndDrawing(flecs::iter& iter, const Window* window);
	};
}

#endif //UNTITLED1_ENGINE_CORE_RENDERINGFEATURE_H_
