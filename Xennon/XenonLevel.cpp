#include "XenonLevel.h"
//#include <cstdlib>

XenonLevel::XenonLevel(Renderer* renderer, int screenWidth, int screenHeight)
{
	rend = renderer;
	screenW = screenWidth;
	screenH = screenHeight;


	background = new Actor("graphics/galaxy2.bmp", renderer, screenWidth, screenHeight, this);
	background->SetSprite(1, 1, false, { 0 }, false);
	background->SetScale(3.f, 4.f);
	background->SetPosition(960, 540);
	AddActor(background);

	std::vector<int> anim = { 89 };
	rightSideparralaxBackground = new BackgroundParallax(renderer, screenWidth, screenHeight, this);
	rightSideparralaxBackground->SetSprite(8, 16, false, anim, false);
	rightSideparralaxBackground->SetScale(5.f, 3.f);
	rightSideparralaxBackground->SetPosition(screenWidth/2, screenHeight - (rightSideparralaxBackground->GetBounds().h));
	AddActor(rightSideparralaxBackground);

	std::vector<int> anim2 = { 186 };
	leftSideparralaxBackground = new BackgroundParallax(renderer, screenWidth, screenHeight, this);
	leftSideparralaxBackground->SetSprite(16, 16, false, anim2, false);
	leftSideparralaxBackground->SetScale(10.f, 5.f);
	leftSideparralaxBackground->SetPosition(screenWidth/2, leftSideparralaxBackground->GetBounds().h);
	AddActor(leftSideparralaxBackground);

	std::vector<int> anim3 = { 171 };
	rightSideparralaxBackground2 = new BackgroundParallax(renderer, screenWidth, screenHeight, this);
	rightSideparralaxBackground2->SetSprite(16, 16, false, anim3, false);
	rightSideparralaxBackground2->SetScale(7.f, 5.f);
	rightSideparralaxBackground2->SetPosition(screenWidth, screenHeight - rightSideparralaxBackground2->GetBounds().h*0.8);
	AddActor(rightSideparralaxBackground2);

	std::vector<int> anim4 = { 346 };
	leftSideparralaxBackground2 = new BackgroundParallax(renderer, screenWidth, screenHeight, this);
	leftSideparralaxBackground2->SetSprite(16, 32, false, anim4, false);
	leftSideparralaxBackground2->SetScale(7.f, 5.f);
	leftSideparralaxBackground2->SetPosition(screenWidth / 3, leftSideparralaxBackground2->GetBounds().h);
	AddActor(leftSideparralaxBackground2);

	leftSideparralaxBackground3 = new BackgroundParallax(renderer, screenWidth, screenHeight, this);
	leftSideparralaxBackground3->SetSprite(16, 32, false, anim4, false);
	leftSideparralaxBackground3->SetScale(10.f, 5.f);
	leftSideparralaxBackground3->SetPosition(0, leftSideparralaxBackground3->GetBounds().h);
	AddActor(leftSideparralaxBackground3);

	playerShip = new Spaceship(renderer, screenWidth, screenHeight, this);
	playerShip->SetPosition((screenWidth / 2) - (playerShip->GetBounds().w / 2), (screenHeight / 2) - (playerShip->GetBounds().h / 2));
	AddActor(playerShip);

	playerLifeCount = new UILifeCounter(renderer, "graphics/PULife.bmp", glm::vec2(40, 900.f));
	playerLifeCount->SetLives(3);
	AddElement(playerLifeCount);

	playerHealthBar = new UIHealthBar(renderer, glm::vec2(35, 1000), glm::vec2(300, 50));
	playerHealthBar->SetHealth(8, 8);
	AddElement(playerHealthBar);

	playerScore = new UIElementText(renderer, "graphics/font16x16.bmp", glm::vec2(1, 1), 3);
	playerScore->SetTextToWrite("Player Score:\n");
	AddTextElement(playerScore);
	highScore = new UIElementText(renderer, "graphics/font16x16.bmp", glm::vec2(900, 1), 2);
	highScore->SetTextToWrite("High Score:\n");
	AddTextElement(highScore);


	
}

void XenonLevel::AddPoints(float pointsToAdd)
{
	if (playerScore && highScore)
	{
		playerScore->AddScoreText(pointsToAdd);
		int playerScoreNumber = playerScore->scoreNumber;
		int highScoreNumber = highScore->scoreNumber;

		if (playerScoreNumber > highScoreNumber)
		{
			highScore->scoreNumber = playerScoreNumber;
		}
	}
}

void XenonLevel::PlayerTookDamage(float currentHealth, float maxHealth)
{
	if (playerHealthBar) {
		playerHealthBar->SetHealth(currentHealth, maxHealth);
	}
}

void XenonLevel::PlayerDied(float livesRemaining)
{
	if (playerLifeCount) {
		playerLifeCount->SetLives(livesRemaining);
	}
}

void XenonLevel::ResetPoints()
{
	if (playerScore)
	{
		playerScore->scoreNumber = 0;
	}
}

void XenonLevel::Update(float deltaTime)
{
	Level::Update(deltaTime);

	countSpawnTimer += deltaTime;

	if (countSpawnTimer >= spawnTimer) {
		SpawnRandomWave();
	}

	if (isSpawningDrones) {
		SpawnDrones(deltaTime);
	}

}

void XenonLevel::SpawnRandomWave()
{
	countSpawnTimer = 0.f;
	randomSpawnNumber = rand() % 5;

	switch (randomSpawnNumber)
	{
	case 0:
		isSpawningDrones = true;
		break;
	case 1:
		SpawnAsteroids();
		break;
	case 2:
		SpawnPickUpCompanion();
		break;
	case 3:
		SpawnRushers();
		break;
	case 4:
		SpawnLoners();
		break;
	default:
		break;
	}
}


void XenonLevel::SpawnDrones(float deltaTime)
{
	countTime += deltaTime;

	if (countTime >= spawnDroneDelay) {
		Drone* drone = new Drone(rend, screenW, screenH, this, 200, 3);
		drone->SetPosition(screenW + 20 , (screenH / 2) - (drone->GetBounds().h / 2));
		AddActor(drone);
		
		countTime = 0;

		++droneCount;

		if (droneCount == maxDronePerWave) {
			drone->isSpecial = true;
			isSpawningDrones = false;
			droneCount = 0;
		}
	}
}

void XenonLevel::SpawnAsteroids()
{
	int howManyAsteroids = rand() % 3;
	++howManyAsteroids;

	for (size_t i = 0; i < howManyAsteroids; ++i)
	{
		int randomAsteroid = rand() % 6;
		std::cout << randomAsteroid << std::endl;

		switch (randomAsteroid)
		{
		case 0: {
			BigAsteroid* bAsteroid = new BigAsteroid(rend, screenW, screenH, this);
			bAsteroid->SetPosition(screenW + bAsteroid->GetBounds().w, glm::clamp((rand() % screenH), 100, screenH - 100) - (bAsteroid->GetBounds().h / 2));
			AddActor(bAsteroid);
			break;
		}

		case 1:
		{
			MediumMetalAsteroids* mMAsteroid = new MediumMetalAsteroids(rend, screenW, screenH, this);
			mMAsteroid->SetPosition(screenW + mMAsteroid->GetBounds().w, glm::clamp((rand() % screenH), 100, screenH - 100) - (mMAsteroid->GetBounds().h / 2));
			AddActor(mMAsteroid);
			break;

		}
		case 2:
		{
			BigMetalAsteroid* bMAsteroid = new BigMetalAsteroid(rend, screenW, screenH, this);
			bMAsteroid->SetPosition(screenW + bMAsteroid->GetBounds().w, glm::clamp((rand() % screenH), 100, screenH - 100) - (bMAsteroid->GetBounds().h / 2));
			AddActor(bMAsteroid);
			break;
		}
		case 3:
		{
			SmallAsteroids* sAsteroid = new SmallAsteroids(rend, screenW, screenH, this);
			sAsteroid->SetPosition(screenW + sAsteroid->GetBounds().w, glm::clamp((rand() % screenH), 100, screenH - 100) - (sAsteroid->GetBounds().h / 2));
			AddActor(sAsteroid);
			break;
		}
		case 4:
		{
			MediumAsteroids* mAsteroid = new MediumAsteroids(rend, screenW, screenH, this);
			mAsteroid->SetPosition(screenW + mAsteroid->GetBounds().w, glm::clamp((rand() % screenH), 100, screenH - 100) - (mAsteroid->GetBounds().h / 2));
			AddActor(mAsteroid);
			break;
		}
		case 5:
		{
			SmallMetalAsteroid* sMAsteroid = new SmallMetalAsteroid(rend, screenW, screenH, this);
			sMAsteroid->SetPosition(screenW + sMAsteroid->GetBounds().w, glm::clamp((rand() % screenH), 100, screenH - 100) - (sMAsteroid->GetBounds().h / 2));
			AddActor(sMAsteroid);
		}
		break;
		default:
			break;
		}

	}

}

void XenonLevel::SpawnLoners()
{
	int howManyLoners = rand() % 5;
	++howManyLoners;

	for (size_t i = 0; i < howManyLoners; i++)
	{
		if (i % 2 != 0) {
			Loner* loner = new Loner(rend, screenW, screenH, this, 1000, 4);
			loner->SetPosition(glm::clamp((rand() % screenW), 500, screenW - 100), 0 );
			loner->moveDown = true;
			AddActor(loner);

		}
		else {
			Loner* loner = new Loner(rend, screenW, screenH, this, 1000, 4);
			loner->SetPosition(glm::clamp((rand() % screenW), 500, screenW - 100), screenH );
			loner->moveUp = true;
			AddActor(loner);

		}
	}

}

void XenonLevel::SpawnRushers()
{
	int howManyRushers = rand() % 5;
	++howManyRushers;

	for (size_t i = 0; i < howManyRushers; i++)
	{
		if (i % 2 != 0) {
			Rusher* rusher = new Rusher(rend, screenW, screenH, this, 1000, 4);
			rusher->SetPosition(-20, glm::clamp((rand() % screenH), 100, screenH - 100));
			rusher->moveFoward = true;
			AddActor(rusher);
		}
		else {
			Rusher* rusher = new Rusher(rend, screenW, screenH, this, 1000, 4);
			rusher->SetPosition(screenW + 20, glm::clamp((rand() % screenH), 100, screenH - 100));
			rusher->moveBackwards = true;
			AddActor(rusher);

		}
	}

	
}

void XenonLevel::SpawnPickUpCompanion()
{
	PickUpCompanion* pickUpCompanion = new PickUpCompanion(rend, screenW, screenH, this);
	pickUpCompanion->SetPosition(screenW + pickUpCompanion->GetBounds().w, glm::clamp((rand() % screenH), 75, screenH - 75) - (pickUpCompanion->GetBounds().h / 2));
	AddActor(pickUpCompanion);
}

