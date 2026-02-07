#pragma once
#include "Actor.h"

class BigMetalAsteroid : public Actor
{
	std::vector<int> anim = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
	float movementSpeed = 150.f;

public:

	BigMetalAsteroid(Renderer* renderer, int screenW, int screenH, Level* level);

	void Update(float deltaTime) override;

	void OnCollisionBegin(Actor* other) override;

};

