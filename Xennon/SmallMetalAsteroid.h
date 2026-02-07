#pragma once
#include "Actor.h"

class SmallMetalAsteroid : public  Actor
{
	std::vector<int> anim = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	float movementSpeed = 150.f;

public:

	SmallMetalAsteroid(Renderer* renderer, int screenW, int screenH, Level* level);

	void Update(float deltaTime) override;

	void OnCollisionBegin(Actor* other) override;
};

