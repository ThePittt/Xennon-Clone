#include "Missile.h"
#include <iostream>

Missile::Missile(Renderer* renderer, int screenW, int screenH, Level* level) : Actor("graphics/missile.bmp", renderer, screenW, screenH, level)
{
	//SetSprite(2, 3, true, anim, true);
	//SetScale(3.f, 3.f);
	//CreateRigidBody(
	//	ActorType::PLAYER_MISSILE,
	//	CollisionCategory::CATEGORY_PLAYER_MISSILE,
	//	{
	//	   CollisionCategory::CATEGORY_ENEMY
	//	}
	//);
}

void Missile::Update(float deltaTime)
{
	Actor::Update(deltaTime);


	positionSize.x += missileSpeed * deltaTime;

	if (positionSize.x <= (0 - positionSize.w) || positionSize.x >= (screenWidth + positionSize.w)
		|| positionSize.y <= (0 - positionSize.h) || positionSize.y >= (screenHeight + positionSize.h)) {
		DestroyActor();
	}
}

void Missile::HitExplosion() {
	Explosion* explosion = new Explosion(renderer, screenWidth, screenHeight, currentLevel);
	explosion->SetPosition(positionSize.x, positionSize.y);
	SpawnActor(explosion);

	DestroyActor();
}

void Missile::OnCollisionBegin(Actor* other)
{
	Actor::OnCollisionBegin(other);
	other->TakeDamage(missileDamage);
	//other->DestroyActor();
	HitExplosion();
}
