#pragma once
#include "Actor.h"
#include "Explosion.h"

class EnemyProjectile : public Actor
{
	std::vector<int> anim = { 0,1,2,3,4,5,6,7 };
	float projectileSpeed = 350.f;
	float projectileDamage = 2;
public:

	EnemyProjectile(Renderer* renderer, int screenW, int screenH, Level* level);

	void Update(float deltaTime) override;

	void HitExplosion();
	void OnCollisionBegin(Actor* other) override;
};

