#pragma once
#include "Pawn.h"
#include "MediumMissile.h"
#include "LightMissile.h"
#include "HeavyMissile.h"
#include "Companion.h"



class Spaceship : public Pawn
{
	std::vector<int> idleAnim = { 3 };
	std::vector<int> turningleftAnim = {2,1,0 };
	std::vector<int> turningRightAnim = {4,5,6 };
	bool onTurningLeftAnim = false;
	bool onTurningRightAnim = false;
	bool isFirstShot = true;

	float time = 0.f;
	float shootCooldown = 0.2f;

	int maxHealth = 8;
	int lives = 3;
	int healing = 2;

	bool onLightMissiles = true;
	bool onMediumMissiles = false;
	bool onHeavyMissiles = false;


	float offset = 100.f;

	Companion* companionA = nullptr;
	Companion* companionB = nullptr;

public:
	Spaceship(Renderer* renderer, int screenW, int screenH, Level* level);

	void Update(float deltaTime) override;

	void Shoot();

	void OnCollisionBegin(Actor* other) override;

	void TakeDamage(float damage) override;

	void UpgradeMissiles();

	void ShieldUpgrade();

	void AddCompanions();

	void RemoveCompanion(Companion* companion);

};

