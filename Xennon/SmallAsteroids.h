#pragma once
#include "Actor.h"

class SmallAsteroids : public Actor
{
	std::vector<int> anim = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	float fowardSpeed = 150.f;
	float sideSpeed = 50.f;

	float points = 50;

public:


	int typeOfAsteroid = 0;

	SmallAsteroids(Renderer* renderer, int screenW, int screenH, Level* level);

	void Update(float deltaTime) override;

	void OnCollisionBegin(Actor* other) override;

	void TakeDamage(float damage) override;
};

