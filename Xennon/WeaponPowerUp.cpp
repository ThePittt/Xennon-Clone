#include "WeaponPowerUp.h"

WeaponPowerUp::WeaponPowerUp(Renderer* renderer, int screenW, int screenH, Level* level) : Actor("graphics/PUWeapon.bmp", renderer, screenW, screenH, level)
{
	SetSprite(4, 2, true, anim, true);
	SetScale(2.f, 2.f);
	CreateRigidBody(
		ActorType::POWERUP_WEAPON,
		CollisionCategory::CATEGORY_POWERUP,
		{
		   CollisionCategory::CATEGORY_PLAYER,
		   CollisionCategory::CATEGORY_COMPANION,
		}
		);
}

void WeaponPowerUp::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	if (positionSize.x < 0 - positionSize.w) {
		DestroyActor();
	}

	positionSize.x -= movementSpeed * deltaTime;
}

void WeaponPowerUp::OnCollisionBegin(Actor* other)
{
	Actor::OnCollisionBegin(other);

	DestroyActor();
}
