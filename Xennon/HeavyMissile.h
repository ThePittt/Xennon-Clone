#pragma once
#include "Missile.h"

class HeavyMissile : public Missile
{
	std::vector<int> anim = { 4,5 };

public:

	HeavyMissile(Renderer* renderer, int screenW, int screenH, Level* level);

};

