#include "Explosion.h"

Explosion::Explosion(Renderer* renderer, int screenW, int screenH, Level* level) : Actor("graphics/explode16.bmp", renderer, screenW, screenH, level)
{
	SetSprite(5, 2, true, anim, false);
	SetScale(2.f, 2.f);
}

void Explosion::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	if (hasAnimationEnded) {
		DestroyActor();
	}
}
