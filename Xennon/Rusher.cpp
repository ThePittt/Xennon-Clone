#include "Rusher.h"
#include "Level.h"

Rusher::Rusher(Renderer* renderer, int screenW, int screenH, Level* level, int score, int enemyHealth) : Actor("graphics/rusher.bmp", renderer, screenW, screenH, level)
{
	health = enemyHealth;
	scorePoints = score;
	SetSprite(4, 6, true, anim, true);
	SetScale(1.5f, 1.5f);
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

void Rusher::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	if (positionSize.x >= screenWidth + 400 || positionSize.x <= -400) {
		
	}

	if (moveBackwards) {
		positionSize.x -= movementSpeed * deltaTime;
	}
	else if (moveFoward) {
		positionSize.x += movementSpeed * deltaTime;
	}

}
void Rusher::OnCollisionBegin(Actor* other)
{
	Actor::OnCollisionBegin(other);
	
}

void Rusher::TakeDamage(float damage)
{
	Actor::TakeDamage(damage);
	if (health <= 0)
	{
		currentLevel->AddPoints(scorePoints);
		DestroyActor();
	}
}
