#include "BackgroundParallax.h"

BackgroundParallax::BackgroundParallax(Renderer* renderer, int screenW, int screenH, Level* level)
	: Actor("graphics/Blocks.bmp", renderer, screenW, screenH, level)
{
	rot = rotation;
}

void BackgroundParallax::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	positionSize.x -= movementSpeed * deltaTime;

	if (positionSize.x < -(positionSize.w * 1.2)) {
		SetPosition((positionSize.w * 1.2) + screenWidth, positionSize.y );
	}
}
