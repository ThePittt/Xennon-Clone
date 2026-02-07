#pragma once
#include "Level.h"
#include <memory>
#include <iostream>
#include "SDL3/SDL.h"

class Window;
class Renderer;


class UnrealityEngine
{

	virtual void OnStart() {}
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnRender() {}

	Window* window;
	Renderer* renderer;
	Level* currentLevel;
	bool isRunning;

	int windowWidth;
	int windowHeight;

public:

	UnrealityEngine();
	~UnrealityEngine();

	void Initialize(std::string title, int width, int height);
	void StartGame();
	void SetCurrentLevel(Level* level);
	Renderer* GetRenderer() { return renderer; };

};

