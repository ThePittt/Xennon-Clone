#pragma once

#include <vector>
#include "Actor.h"
#include "UIElement.h"
#include "UIElementText.h"
#include "box2d/box2d.h"

class Level
{
	std::vector<Actor*> actors;	
	std::vector<UIElement*> uiElements;
	std::vector<UIElementText*> uiTextElements;

public:
	Level();
	~Level();

	virtual void Update(float deltaTime);

	void FixedUpdate(float timeStep, float subStepCount);

	void PhysicsCollisions();

	void Render(Renderer* renderer);

	void AddActor(Actor* actor);

	void AddElement(UIElement* element);

	void AddTextElement(UIElementText* textElement);

	void RemoveActor();

	void RemoveTextElement();

	virtual void AddPoints(float pointsToAdd);

	virtual void PlayerTookDamage(float currentHealth, float maxHealth);

	virtual void PlayerDied(float livesRemaining);

	virtual void ResetPoints();

	b2WorldId worldId;

};

