#pragma once
#include "Actor.h"
#include "MediumMissile.h"
#include "LightMissile.h"
#include "HeavyMissile.h"
class Spaceship;

class Companion : public Actor
{
	std::vector<int> anim = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

	float offset = 2.f;

	bool onLightMissiles = true;
	bool onMediumMissiles = false;
	bool onHeavyMissiles = false;

	Spaceship* playerSpaceship = nullptr;

	int maxHealth = 4;
	int healing = 1;

public:

	Companion(Renderer* renderer, int screenW, int screenH, Level* level, Spaceship* spaceship);

	void Update(float deltaTime) override;

	void OnCollisionBegin(Actor* other) override;

	void AddSpaceship(Spaceship* ship);

	void Move(float positionX, float positionY);

	void Shoot();

	void UpgradeMissiles();

	void ShieldUpgrade();

	void TakeDamage(float damage) override;

	void Dead();

};

