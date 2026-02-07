#include "MediumAsteroids.h"
#include "Level.h"

MediumAsteroids::MediumAsteroids(Renderer* renderer, int screenW, int screenH, Level* level) : Actor("graphics/SAster64.bmp", renderer, screenW, screenH, level)
{
	health = 6;
	SetSprite(8, 3, true, anim, true);
	SetScale(1.f, 1.f);
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

void MediumAsteroids::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	if (positionSize.x < 0 - positionSize.w || (positionSize.y < (0 - positionSize.h)) || (positionSize.y > (screenHeight + positionSize.h))) {
		DestroyActor();
	}

	switch (typeOfAsteroid)
	{
	case 0:
		positionSize.x -= fowardSpeed * deltaTime;
		break;
	case 1:
		positionSize.x -= fowardSpeed * deltaTime;
		positionSize.y -= sideSpeed * deltaTime;
		break;
	case 2:
		positionSize.x -= fowardSpeed * deltaTime;
		positionSize.y += sideSpeed * deltaTime;
		break;
	default:
		positionSize.x -= fowardSpeed * deltaTime;
		break;
	}

	
}

void MediumAsteroids::OnCollisionBegin(Actor* other)
{
	Actor::OnCollisionBegin(other);
}

void MediumAsteroids::SeparateIntoSmallerRocks()
{
	for (int i = 0; i < 3; ++i)
	{

		SmallAsteroids* smallerAsteroid = new SmallAsteroids(renderer, screenWidth, screenHeight, currentLevel);
		smallerAsteroid->SetPosition(positionSize.x, positionSize.y);
		smallerAsteroid->typeOfAsteroid = i;
		SpawnActor(smallerAsteroid);
	}
}
void MediumAsteroids::TakeDamage(float damage)
{
	Actor::TakeDamage(damage);
	if (health <= 0)
	{
		currentLevel->AddPoints(points);
		SeparateIntoSmallerRocks();
		DestroyActor();
	}
}