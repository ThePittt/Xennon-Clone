#pragma once
#include "Level.h"
#include "UnrealityEngine.h"
#include "Actor.h"
#include "Spaceship.h"
#include "Rusher.h"
#include "Loner.h"
#include "UILifeCounter.h"
#include "UIHealthBar.h"
#include "UIElementText.h"
#include "BackgroundParallax.h"

#include "Drone.h"
#include "BigAsteroid.h"
#include "BigMetalAsteroid.h"
#include "MediumMetalAsteroids.h"
#include "SmallMetalAsteroid.h"
#include "PickUpCompanion.h"

class XenonLevel : public Level
{
	Actor* background;
	BackgroundParallax* rightSideparralaxBackground;
	BackgroundParallax* leftSideparralaxBackground;
	BackgroundParallax* rightSideparralaxBackground2;
	BackgroundParallax* leftSideparralaxBackground2;
	BackgroundParallax* leftSideparralaxBackground3;
	Spaceship* playerShip;

	//UI
	UILifeCounter* playerLifeCount;
	UIHealthBar* playerHealthBar;
	UIElementText* playerScore;
	UIElementText* highScore;

	Renderer* rend;
	int screenW;
	int screenH;
public:
	// Constructor takes renderer to load images
	XenonLevel(Renderer* renderer, int screenWidth, int screenHeight);

	// We can add specific destructors if we need to clean up unique pointers
	~XenonLevel() = default;

	void AddPoints(float pointsToAdd) override;

	void PlayerTookDamage(float currentHealth, float maxHealth) override;

	void PlayerDied(float livesRemaining) override;

	void ResetPoints() override;

	void Update(float deltaTime) override;

protected:
	int randomSpawnNumber = 0;
	float spawnTimer = 3.f;
	float countSpawnTimer = 0.f;
	void SpawnRandomWave();



	float countTime = 0.f;
	float spawnDroneDelay = .3f;
	bool isSpawningDrones = false;
	int maxDronePerWave = 8;
	int droneCount = 0;

	void SpawnDrones(float deltaTime);


	void SpawnAsteroids();

	void SpawnLoners();

	void SpawnRushers();

	void SpawnPickUpCompanion();

};

