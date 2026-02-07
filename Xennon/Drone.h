#pragma once
#include "Actor.h"
#include "WeaponPowerUp.h"
#include "ShieldPowerUp.h"

class Drone : public Actor
{
	std::vector<int> anim = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	float movementSpeed = 200.f;
	float waveSpeed = 3.f;
	float waveLenght = 200.f;

	bool moveUp = false;
	bool moveDown = true;

	

	float startPositionX = 0.f;
	bool isInitialized = false;

	float totalTime = 0.f;

	int scorePoints;
public:
	bool isSpecial = false;
	Drone(Renderer* renderer, int screenW, int screenH, Level* level, int score, int enemyHealth);

	void Update(float deltaTime) override;
	
	void OnCollisionBegin(Actor* other) override;

	void SpawnPowerUps();

	void TakeDamage(float damage) override;
};

