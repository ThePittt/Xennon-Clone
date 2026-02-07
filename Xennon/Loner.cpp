#include "Loner.h"
#include "Level.h"
#include <iostream>

Loner::Loner(Renderer* renderer, int screenW, int screenH, Level* level, int score, int enemyHealth) : Actor("graphics/LonerA.bmp", renderer, screenW, screenH, level)
{
	health = enemyHealth;
	scorePoints = score;
	SetSprite(4, 4, true, anim, true);
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

void Loner::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	time += deltaTime;

	if (positionSize.y >= screenHeight + 400 || positionSize.y <= -400) {
		DestroyActor();
		std::cout << "Loner is dead" << std::endl;
	}


	if (moveUp) {
		positionSize.y -= movementSpeed * deltaTime;
	}
	else if (moveDown) {
		positionSize.y += movementSpeed * deltaTime;
	}
	
	if (time >= cooldown) {
		Shoot();
		time = 0.f;
	}
	
}

void Loner::Shoot() {
	EnemyProjectile* projectile = new EnemyProjectile(renderer, screenWidth, screenHeight, currentLevel);
	projectile->SetPosition(positionSize.x - (positionSize.w / 4), positionSize.y);
	SpawnActor(projectile);
}

void Loner::OnCollisionBegin(Actor* other)
{
	Actor::OnCollisionBegin(other);
}

void Loner::TakeDamage(float damage)
{
	Actor::TakeDamage(damage);
	if (health <= 0)
	{
		currentLevel->AddPoints(scorePoints);
		DestroyActor();
	}
}

