#pragma once
#include "Actor.h"
#include "Explosion.h"

class Missile : public Actor
{
	std::vector<int> anim = { 0,1 };

	float missileSpeed = 1200.f;
	
public:
	float missileDamage = 1;
	Missile(Renderer* renderer, int screenW, int screenH, Level* level);

	void Update(float deltaTime) override;

	void HitExplosion();

	void OnCollisionBegin(Actor* other) override;
};

