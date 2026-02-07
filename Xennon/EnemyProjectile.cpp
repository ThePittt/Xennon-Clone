#include "EnemyProjectile.h"

EnemyProjectile::EnemyProjectile(Renderer* renderer, int screenW, int screenH, Level* level) 
	: Actor("graphics/EnWeap6.bmp", renderer, screenW, screenH, level)
{
	SetSprite(8, 1, true, anim, true);
	SetScale(3.f, 3.f);
	CreateRigidBody(
		ActorType::ENEMY_MISSILE,
		CollisionCategory::CATEGORY_ENEMY_MISSILE,
		{
		   CollisionCategory::CATEGORY_PLAYER,
		   CollisionCategory::CATEGORY_COMPANION

		}
	);
}

void EnemyProjectile::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	positionSize.x -= projectileSpeed * deltaTime;

	if (positionSize.x <= (0 - positionSize.w) || positionSize.x >= (screenWidth + positionSize.w) 
			|| positionSize.y <= (0 - positionSize.h) || positionSize.y >= (screenHeight + positionSize.h)) {
		DestroyActor();
	}
}

void EnemyProjectile::HitExplosion()
{
	Explosion* explosion = new Explosion(renderer, screenWidth, screenHeight, currentLevel);
	explosion->SetPosition(positionSize.x, positionSize.y);
	SpawnActor(explosion);
	DestroyActor();
}

void EnemyProjectile::OnCollisionBegin(Actor* other)
{
	Actor::OnCollisionBegin(other);
	other->TakeDamage(projectileDamage);
	HitExplosion();
}
