#pragma once
#include "Actor.h"

class WeaponPowerUp : public Actor
{
	std::vector<int> anim = { 0,1,2,3,4,5,6,7 };
	float movementSpeed = 150.f;

public:

	WeaponPowerUp(Renderer* renderer, int screenW, int screenH, Level* level);

	void Update(float deltaTime) override;

	void OnCollisionBegin(Actor* other) override;
};

