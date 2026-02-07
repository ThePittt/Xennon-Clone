#include "Spaceship.h"
#include "Level.h"
#include <vector>
#include <iostream>

Spaceship::Spaceship(Renderer* renderer, int screenW, int screenH, Level* level) : Pawn("graphics/Ship1.bmp", renderer, screenW, screenH, level)
{
	health = maxHealth;

	SetSpeed(600.0f);
	SetSprite(7, 1, false, idleAnim, true);
	SetScale(1.8f, 1.8f);
	CreateRigidBody(
		ActorType::PLAYER,
		CollisionCategory::CATEGORY_PLAYER,
		{
		   CollisionCategory::CATEGORY_ENEMY,
		   CollisionCategory::CATEGORY_ENEMY_MISSILE,
		   CollisionCategory::CATEGORY_POWERUP
		}
	);

}

void Spaceship::Update(float deltaTime)
{
	Pawn::Update(deltaTime);

	time += deltaTime;

	if (movingBackwards) {
		useAnimation = true;
		if (!onTurningRightAnim) {

			SetNewAnimation(turningRightAnim, 7, 3, false);
			onTurningRightAnim = true;
			onTurningLeftAnim = false;
		}

	}
	else if (movingFoward) {
		useAnimation = true;

		if (!onTurningLeftAnim) {
			SetNewAnimation(turningleftAnim, 7, 3, false);
			onTurningRightAnim = false;
			onTurningLeftAnim = true;
		}

	}
	else {
		useAnimation = false;
		onTurningRightAnim = false;
		onTurningLeftAnim = false;
	}
	if (companionA != nullptr) {
		companionA->Move(positionSize.x, positionSize.y + offset);
	}
	if (companionB != nullptr) {
		companionB->Move(positionSize.x, positionSize.y - offset);
	}

	if (playerShoot) {
		if (isFirstShot) {
			Shoot();
			isFirstShot = false;
			time = 0.f;
		}
		else if (time >= shootCooldown) {
			Shoot();
			time = 0.f;
		}
	}


}

void Spaceship::Shoot()
{
	Missile* missile;

	if (onLightMissiles) {
		missile = new LightMissile(renderer, screenWidth, screenHeight, currentLevel);
	}
	else if (onMediumMissiles) {
		missile = new MediumMissile(renderer, screenWidth, screenHeight, currentLevel);
	}
	else {
		missile = new HeavyMissile(renderer, screenWidth, screenHeight, currentLevel);
	}
	missile->SetPosition(positionSize.x + (positionSize.w / 4), positionSize.y);
	SpawnActor(missile);

	if (companionA != nullptr) {
		companionA->Shoot();
	}
	if (companionB != nullptr) {
		companionB->Shoot();
	}
}

void Spaceship::OnCollisionBegin(Actor* other)
{
	Actor::OnCollisionBegin(other);
	if (other->GetActorType() == ActorType::POWERUP_SHIELD) {
		ShieldUpgrade();
	}
	else if (other->GetActorType() == ActorType::POWERUP_WEAPON) {
		UpgradeMissiles();
	}
	else if (other->GetActorType() == ActorType::POWERUP_COMPANION) {
		AddCompanions();
		std::cout << "OnCollision" << std::endl;
	}
	else if (other->GetActorType() == ActorType::ENEMY) {
		TakeDamage(1);
	}
	
}

void Spaceship::TakeDamage(float damage)
{
	Actor::TakeDamage(damage);
	health = glm::clamp(health, 0, maxHealth);

	if (health <= 0)
	{
		health = 0;
		--lives; // Remove Life
		if (lives > 0)
		{
			health = maxHealth; // Respawn
		}

		if (companionA != nullptr) {
			companionA->Dead();
		}
		if (companionB != nullptr) {
			companionB->Dead();
		}

		currentLevel->PlayerDied(lives);
		currentLevel->ResetPoints();
	}
	currentLevel->PlayerTookDamage(health, maxHealth);
}


void Spaceship::UpgradeMissiles()
{
	if (onLightMissiles) {
		onLightMissiles = false;
		onMediumMissiles = true;
	}
	else if (onMediumMissiles) {
		onMediumMissiles = false;
		onHeavyMissiles = true;
	}
}

void Spaceship::ShieldUpgrade()
{
	health += healing;
	health = glm::clamp(health, 0, maxHealth);
	currentLevel->PlayerTookDamage(health, maxHealth);
}

void Spaceship::AddCompanions()
{
	if (companionA == nullptr) {
		std::cout << "Hello" << std::endl;
		companionA = new Companion(renderer, screenWidth, screenHeight, currentLevel, this);
		companionA->SetPosition(positionSize.x, positionSize.y + offset );
		SpawnActor(companionA);
	}
	else if (companionB == nullptr) {
		companionB = new Companion(renderer, screenWidth, screenHeight, currentLevel, this);
		companionB->SetPosition(positionSize.x, positionSize.y - offset);
		SpawnActor(companionB);
	}

	std::cout << "Nothing" << std::endl;

}

void Spaceship::RemoveCompanion(Companion* companion)
{
	if (companion == companionA) {
		companionA = nullptr;
	}
	else if (companion == companionB) {
		companionB = nullptr;
	}
}

