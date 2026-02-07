#include "Drone.h"
#include "Level.h"

Drone::Drone(Renderer* renderer, int screenW, int screenH, Level* level, int score, int enemyHealth) : Actor("graphics/drone.bmp", renderer, screenW, screenH, level)
{
	rotation = 0;
	scorePoints = score;
	health = enemyHealth;
	SetSprite(8, 2, true, anim, true);
	SetScale(2.f, 2.f);
	CreateRigidBody(
		ActorType::ENEMY,
		CollisionCategory::CATEGORY_ENEMY,
		{
		   CollisionCategory::CATEGORY_PLAYER,
		   CollisionCategory::CATEGORY_PLAYER_MISSILE,
		   CollisionCategory::CATEGORY_COMPANION
		}
	);
	
}

void Drone::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	if (!isInitialized) {
		startPositionX = positionSize.y;
		isInitialized = true;
	}

	if (positionSize.x <= -200) {
		DestroyActor();
	}

	positionSize.x -= movementSpeed * deltaTime;


	totalTime += deltaTime;

	float offset = std::sin(waveSpeed * totalTime) * waveLenght;

	positionSize.y = startPositionX + offset;

}

void Drone::OnCollisionBegin(Actor* other)
{
	Actor::OnCollisionBegin(other);
}

void Drone::SpawnPowerUps()
{
	int randomPowerUp = rand() % 2;

	switch (randomPowerUp)
	{
	case 0: {
		ShieldPowerUp* powerUp = new ShieldPowerUp(renderer, screenWidth, screenHeight, currentLevel);
		powerUp->SetPosition(positionSize.x, positionSize.y);
		SpawnActor(powerUp);
		break;
	}
	case 1: {
		WeaponPowerUp* powerUp = new WeaponPowerUp(renderer, screenWidth, screenHeight, currentLevel);
		powerUp->SetPosition(positionSize.x, positionSize.y);
		SpawnActor(powerUp);
		break;
	}
	default: {
		WeaponPowerUp* powerUp = new WeaponPowerUp(renderer, screenWidth, screenHeight, currentLevel);
		powerUp->SetPosition(positionSize.x, positionSize.y);
		SpawnActor(powerUp);
		break;
	}
	}

}
void Drone::TakeDamage(float damage)
{
	Actor::TakeDamage(damage);
	if (health <= 0)
	{
		currentLevel->AddPoints(scorePoints);
		if (isSpecial) {
			SpawnPowerUps();
		}
		DestroyActor();
	}
}
