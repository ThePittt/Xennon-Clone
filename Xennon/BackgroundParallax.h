#pragma once
#include "Actor.h"

class BackgroundParallax : public Actor
{
	std::vector<int> anim = { 89 };
	float movementSpeed = 75.f;

	float time = 0.f;
	float cooldown = 5.f;

	float rot = 270;

public:

	BackgroundParallax(Renderer* renderer, int screenW, int screenH, Level* level);

	void Update(float deltaTime) override;

};

