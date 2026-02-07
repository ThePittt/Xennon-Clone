#pragma once
#include "Actor.h"
#include "SmallAsteroids.h"

class MediumAsteroids : public Actor
{
	std::vector<int> anim = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };
	float fowardSpeed = 150.f;
	float sideSpeed = 50.f;

	float points = 100;
public:

	int typeOfAsteroid = 0;

	MediumAsteroids(Renderer* renderer, int screenW, int screenH, Level* level);

	void Update(float deltaTime) override;

	void OnCollisionBegin(Actor* other) override;

	void SeparateIntoSmallerRocks();

	void TakeDamage(float damage) override;
};

