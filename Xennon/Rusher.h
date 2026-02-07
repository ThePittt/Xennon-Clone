#pragma once
#include "Actor.h"

class Rusher : public Actor
{
	std::vector<int> anim = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };
	float movementSpeed = 400.f;
	

	int scorePoints;
public:

	bool moveFoward = false;
	bool moveBackwards = false;

	Rusher(Renderer* renderer, int screenW, int screenH, Level* level, int score, int enemyHealth);

	void Update(float deltaTime) override;

	void OnCollisionBegin(Actor* other) override;
	void TakeDamage(float damage) override;
};

