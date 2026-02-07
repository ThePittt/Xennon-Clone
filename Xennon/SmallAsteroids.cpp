#include "SmallAsteroids.h"
#include "Level.h"

SmallAsteroids::SmallAsteroids(Renderer* renderer, int screenW, int screenH, Level* level) : Actor("graphics/SAster32.bmp", renderer, screenW, screenH, level)
{
	health = 3;
	SetSprite(8, 2, true, anim, true);
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

void SmallAsteroids::Update(float deltaTime)
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

void SmallAsteroids::OnCollisionBegin(Actor* other)
{
	Actor::OnCollisionBegin(other);

	if (other->GetActorType() == ActorType::PLAYER_MISSILE) {
		DestroyActor();
	}
}
void SmallAsteroids::TakeDamage(float damage)
{
	Actor::TakeDamage(damage);
	if (health <= 0)
	{
		currentLevel->AddPoints(points);
		DestroyActor();
	}
}
