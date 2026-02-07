#include "SmallMetalAsteroid.h"

SmallMetalAsteroid::SmallMetalAsteroid(Renderer* renderer, int screenW, int screenH, Level* level) : Actor("graphics/GAster32.bmp", renderer, screenW, screenH, level)
{
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

void SmallMetalAsteroid::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	if (positionSize.x < 0 - positionSize.w) {
		DestroyActor();
	}

	positionSize.x -= movementSpeed * deltaTime;
}

void SmallMetalAsteroid::OnCollisionBegin(Actor* other)
{
	Actor::OnCollisionBegin(other);
}
