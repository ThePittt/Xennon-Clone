#pragma once
#include "Actor.h"

#include "EnemyProjectile.h"


class Loner : public Actor
{
	std::vector<int> anim = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	float movementSpeed = glm::clamp((rand() % 3) * 100, 75, 300);


	float time = 0.f;
	float cooldown = 5.f;

	int scorePoints;

public:

	bool moveUp = false;
	bool moveDown = false;

	Loner(Renderer* renderer, int screenW, int screenH, Level* level, int score, int enemyHealth);

	void Update(float deltaTime) override;

	void Shoot();

	void OnCollisionBegin(Actor* other) override;

	void TakeDamage(float damage) override;
};


