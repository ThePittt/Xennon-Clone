#include "pch.h"
#include "UnrealityEngine.h"
#include <iostream>
#include "Window.h"
#include "Renderer.h"

UnrealityEngine::UnrealityEngine()
	: window(nullptr), renderer(nullptr), currentLevel(nullptr), isRunning(false)
{
}

UnrealityEngine::~UnrealityEngine()
{
	delete renderer;
	delete window;
}

void UnrealityEngine::Initialize(std::string title, int width, int height)
{
	SDL_Init(SDL_INIT_GAMEPAD);
	window = new Window(title, width, height);
	renderer = new Renderer(window);
}

void UnrealityEngine::StartGame()
{
	isRunning = true;

	Uint64 prevTime = SDL_GetTicks();
	Uint64 currentTime;
	float deltaTime;
	float accumulator = 0;
	float fixedStep = 1.0f / 60.0f;
	SDL_Event ev;

	while (isRunning) {

		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;
		prevTime = currentTime;

		while (SDL_PollEvent(&ev)) {
			// Getting the events
			if (ev.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}
		}

		currentLevel->Update(deltaTime);

		
		accumulator += deltaTime;
		if (accumulator >= fixedStep)
		{
			currentLevel->FixedUpdate(fixedStep, 4);
			accumulator -= fixedStep;
		}

		renderer->SetRendererClear();

		currentLevel->Render(renderer);

		renderer->SetRendererPresent();
	}

}

void UnrealityEngine::SetCurrentLevel(Level* level)
{
	currentLevel = level;
}




