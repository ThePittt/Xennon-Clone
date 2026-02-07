#include "MediumMissile.h"

MediumMissile::MediumMissile(Renderer* renderer, int screenW, int screenH, Level* level) : Missile(renderer, screenW, screenH, level)
{
	missileDamage = 2;
	SetSprite(2, 3, true, anim, true);
	SetScale(3.f, 3.f);
	CreateRigidBody(
		ActorType::PLAYER_MISSILE,
		CollisionCategory::CATEGORY_PLAYER_MISSILE,
		{
		   CollisionCategory::CATEGORY_ENEMY
		}
	);

}


