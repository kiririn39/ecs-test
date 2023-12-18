//
// Created by Vlad Boroday on 2023-12-03.
//

#include "RenderingFeature.h"
#include "Engine/GlobaEntities.h"

void SEngine::RenderingFeature::RegisterTypes(flecs::world& world)
{
	world.entity<RenderPhases::PreDraw>().add(flecs::Phase).depends_on(flecs::OnStore);
	world.entity<RenderPhases::Draw>().add(flecs::Phase).depends_on<RenderPhases::PreDraw>();
	world.entity<RenderPhases::PostDraw>().add(flecs::Phase).depends_on<RenderPhases::Draw>();
	world.entity(flecs::PostFrame).add(flecs::Phase).depends_on<RenderPhases::PostDraw>();
}

void SEngine::RenderingFeature::RegisterSystem(flecs::world& world)
{
	world.observer<Window>("Window Lifecycle Manager")
		.event(flecs::OnAdd)
		.event(flecs::OnRemove)
		.iter(WindowLifecycleHandler);

	world.observer<Window, const WindowTitle>("Update window title")
		.event(flecs::OnSet)
		.iter(UpdateWindowTitle);

	world.observer<Window, const WindowSize>("Update window size")
		.event(flecs::OnSet)
		.each(UpdateWindowSize);

	world.system<Window>("Check exit request")
		.kind(flecs::PostFrame)
		.iter(CheckExitRequest);

	world.system<Window>("Begin drawing")
		.kind<RenderPhases::PreDraw>()
		.iter(BeginDrawing);

	world.system<Position, TextureComponent>("Draw textures")
		.kind<RenderPhases::Draw>()
		.each(DrawTextureEntities);

	world.system<Position, TextComponent>("Draw Texts")
		.kind<RenderPhases::Draw>()
		.each(DrawTextEntities);

	world.system<Window>("End drawing")
		.kind<RenderPhases::PostDraw>()
		.iter(EndDrawing);
}

void SEngine::RenderingFeature::CheckExitRequest(flecs::iter& iter, const SEngine::Window* window)
{
	for (auto& i : iter)
	{
		if (window[i].WindowHandle->ShouldClose())
		{
			window[i].WindowHandle->Close();
			iter.world().quit();
		}
	}
}

void SEngine::RenderingFeature::InitGlobals(flecs::world& world)
{
	float screenWidth = 1600;
	float screenHeight = 1000;

	MainCamera = world.entity("Main camera")
		.add<CameraDimensions>();

	world.component<MainWindow>()
		.add<Window>()
		.set<WindowSize>({{ screenWidth, screenHeight }})
		.set<WindowTitle>({ "raylib-cpp - basic window" });
}

void SEngine::RenderingFeature::WindowLifecycleHandler(flecs::iter& iter, SEngine::Window* window)
{
	if (iter.event() == flecs::OnAdd)
	{
		for (auto& i : iter)
		{
			window[i].WindowHandle = new raylib::Window(1600, 900);
			window[i].WindowHandle->SetTargetFPS(0);
		}
	}
	else if (iter.event() == flecs::OnRemove)
	{
		for (auto& i : iter)
		{
			delete window[i].WindowHandle;
		}
	}
}

void SEngine::RenderingFeature::UpdateWindowTitle(flecs::iter& iter,
	const SEngine::Window* window,
	const SEngine::WindowTitle* title)
{
	if (iter.event_id() == flecs::type_id<WindowTitle>())
	{
		for (auto& i : iter)
		{
			window[i].WindowHandle->SetTitle(title[i].Title);
		}
	}
}

void SEngine::RenderingFeature::UpdateWindowSize(
	SEngine::Window& window,
	const SEngine::WindowSize& size)
{
	window.WindowHandle->SetSize(size.Dimension);
	MainCamera.get_mut<CameraDimensions>()->Value = size.Dimension;
}

void SEngine::RenderingFeature::BeginDrawing(flecs::iter& iter, const SEngine::Window* window)
{
	for (auto i : iter)
	{
		window[i].WindowHandle->BeginDrawing();
		window[i].WindowHandle->ClearBackground();
	}
}

void SEngine::RenderingFeature::EndDrawing(flecs::iter& iter, const SEngine::Window* window)
{
	for (auto i : iter)
	{
		DrawFPS(10, 10);
		window[i].WindowHandle->EndDrawing();
	}
}
void SEngine::RenderingFeature::DrawTextureEntities(
	const SEngine::Position& position,
	const SEngine::TextureComponent& texture)
{
	Vector2 Size = texture.Id.GetSize();
	texture.Id.Draw(position.LocalPosition - (Size * texture.DrawOrigin));
}

void SEngine::RenderingFeature::DrawTextEntities(const SEngine::Position& position,
	const SEngine::TextComponent& textComponent)
{
	Vector2 size = textComponent.Text.MeasureEx();
	textComponent.Text.Draw(position.LocalPosition, 0.0f, size * textComponent.DrawOrigin);
}
