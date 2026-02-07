#pragma once
#include "Missile.h"

class LightMissile : public Missile
{
	std::vector<int> anim = { 0,1 };

public:

	LightMissile(Renderer* renderer, int screenW, int screenH, Level* level);
};

