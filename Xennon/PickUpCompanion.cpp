#include "PickUpCompanion.h"

PickUpCompanion::PickUpCompanion(Renderer* renderer, int screenW, int screenH, Level* level) : Actor("graphics/clone.bmp", renderer, screenW, screenH, level)
{
	SetSprite(4, 5, true, anim, true);
	SetScale(2.f, 2.f);
	CreateRigidBody(
		ActorType::POWERUP_COMPANION,
		CollisionCategory::CATEGORY_POWERUP,
		{
		   CollisionCategory::CATEGORY_PLAYER,
		}
	);
}

void PickUpCompanion::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	if (positionSize.x < 0 - positionSize.w) {
		DestroyActor();
	}

	positionSize.x -= movementSpeed * deltaTime;
}

void PickUpCompanion::OnCollisionBegin(Actor* other)
{
	Actor::OnCollisionBegin(other);

	DestroyActor();
}

