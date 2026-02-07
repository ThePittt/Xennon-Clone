#include "BigAsteroid.h"
#include "Level.h"

BigAsteroid::BigAsteroid(Renderer* renderer, int screenW, int screenH, Level* level) : Actor("graphics/SAster96.bmp", renderer, screenW, screenH, level)
{
	health = 9;
	SetSprite(5, 5, true, anim, true);
	SetScale(2.f, 2.f);
	CreateRigidBody(
		ActorType::ENEMY,
		CollisionCategory::CATEGORY_ENEMY,
		{
		   CollisionCategory::CATEGORY_PLAYER,
		   CollisionCategory::CATEGORY_PLAYER_MISSILE,
		   CollisionCategory::CATEGORY_COMPANION,

		}
	);
}

void BigAsteroid::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	if (positionSize.x < 0 - positionSize.w) {
		DestroyActor();
	}

	positionSize.x -= movementSpeed * deltaTime;
}

void BigAsteroid::OnCollisionBegin(Actor* other)
{
	Actor::OnCollisionBegin(other);

}

void BigAsteroid::SeparateIntoSmallerRocks()
{
	for (int i = 0; i < 3; ++i)
	{
		
		MediumAsteroids* smallerAsteroid = new MediumAsteroids(renderer, screenWidth, screenHeight, currentLevel);
		smallerAsteroid->SetPosition(positionSize.x, positionSize.y);
		smallerAsteroid->typeOfAsteroid = i;
		SpawnActor(smallerAsteroid);
	}
}

void BigAsteroid::TakeDamage(float damage)
{
	Actor::TakeDamage(damage);
	if (health <= 0)
	{
		currentLevel->AddPoints(points);
		SeparateIntoSmallerRocks();
		DestroyActor();
	}
}
