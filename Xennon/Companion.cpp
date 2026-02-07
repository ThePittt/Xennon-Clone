#include "Companion.h"
#include "Spaceship.h"

Companion::Companion(Renderer* renderer, int screenW, int screenH, Level* level, Spaceship* spaceship) : Actor("graphics/clone.bmp", renderer, screenW, screenH, level)
{
	health = maxHealth;
	playerSpaceship = spaceship;

	SetSprite(4, 5, true, anim, true);
	SetScale(2.f, 2.f);
	CreateRigidBody(
		ActorType::PLAYER,
		CollisionCategory::CATEGORY_COMPANION,
		{
		   CollisionCategory::CATEGORY_ENEMY_MISSILE,
		   CollisionCategory::CATEGORY_ENEMY,
		   CollisionCategory::CATEGORY_POWERUP
		}
		);
}

void Companion::Update(float deltaTime)
{
	Actor::Update(deltaTime);
}

void Companion::OnCollisionBegin(Actor* other)
{
	Actor::OnCollisionBegin(other);
	if (other->GetActorType() == ActorType::POWERUP_SHIELD) {
		ShieldUpgrade();
	}
	else if (other->GetActorType() == ActorType::POWERUP_WEAPON) {
		UpgradeMissiles();
	}
	else if (other->GetActorType() == ActorType::ENEMY) {
		TakeDamage(1);
	}
	//playerSpaceship->RemoveCompanion(this);
}

void Companion::AddSpaceship(Spaceship* ship)
{
	playerSpaceship = ship;
}

void Companion::Move(float positionX, float positionY)
{
	positionSize.x = positionX;
	positionSize.y = positionY;
}

void Companion::Shoot()
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
}

void Companion::UpgradeMissiles()
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

void Companion::ShieldUpgrade()
{
	health += healing;
	health = glm::clamp(health, 0, maxHealth);
}

void Companion::TakeDamage(float damage)
{
	Actor::TakeDamage(damage);
	if (health <= 0)
	{
		Dead();
	}
}

void Companion::Dead()
{
	playerSpaceship->RemoveCompanion(this);
	DestroyActor();	
}
