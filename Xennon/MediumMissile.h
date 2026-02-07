#pragma once
#include "Missile.h"

class MediumMissile : public Missile
{

	std::vector<int> anim = { 2,3 };

public:

	MediumMissile(Renderer* renderer, int screenW, int screenH, Level* level);
};

