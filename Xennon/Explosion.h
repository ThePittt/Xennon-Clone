#pragma once
#include "Actor.h"

class Explosion : public Actor
{
	std::vector<int> anim = { 0,1,2,3,4,5,6,7,8,9 };

	
public:

	Explosion(Renderer* renderer, int screenW, int screenH, Level* level);

	void Update(float deltaTime) override;

};

