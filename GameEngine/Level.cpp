#include "pch.h"
#include "Level.h"

#include "UnrealityEngine.h"


Level::Level()
{
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = b2Vec2{ 0.0f, 0.0f }; // Gravity pointing down

	worldDef.enableSleep = false;  // Disable sleeping
	worldDef.enableContinuous = true;  // Enable continuous collision detection

	// Create the world using RAII principles
	worldId = b2CreateWorld(&worldDef);
}

Level::~Level()
{
	for (Actor* actor : actors) {
		delete actor;
	}
	for (UIElement* uiElement : uiElements) {
		delete uiElement;
	}
	for (UIElementText* uiElementText : uiTextElements) {
		delete uiElementText;
	}

	actors.clear();
	uiElements.clear();
	uiTextElements.clear();
	b2DestroyWorld(worldId);
}


void Level::Update(float deltaTime)
{
	for (int i = 0; i < actors.size(); ++i) {
		actors[i]->Update(deltaTime);
	}
	RemoveActor();
}
void Level::FixedUpdate(float timeStep, float subStepCount)
{
	for (int i = 0; i < actors.size(); ++i) {
		actors[i]->UpdateRigidbodies();
	}
	b2World_Step(worldId, timeStep, subStepCount);

	for (int i = 0; i < actors.size(); ++i) {
		actors[i]->SyncFromPhysics();
	}
	PhysicsCollisions();
}

void Level::PhysicsCollisions()
{
	b2ContactEvents contactEvents = b2World_GetContactEvents(worldId);

	for (int i = 0; i < contactEvents.beginCount; ++i)
	{
		std::cout << "Collisions happened" << std::endl;
		b2ContactBeginTouchEvent* beginEvent = &contactEvents.beginEvents[i];
		b2ShapeId shapeIdA = beginEvent->shapeIdA;
		b2ShapeId shapeIdB = beginEvent->shapeIdB;

		Actor* actorA = static_cast<Actor*>(b2Shape_GetUserData(shapeIdA));
		Actor* actorB = static_cast<Actor*>(b2Shape_GetUserData(shapeIdB));

		std::cout << actorA << actorB << std::endl;

		if (actorA && actorB)
		{
			actorA->OnCollisionBegin(actorB);
			if (actorA && actorB)
			{
				actorB->OnCollisionBegin(actorA);
			}

		}
	}

}

void Level::Render(Renderer* renderer) {
	for (Actor* actor : actors) {
		actor->Render(renderer);
	}
	for (UIElement* uiElement : uiElements) {
		uiElement->Draw();
	}
	for (UIElementText* uiElementText : uiTextElements) {
		uiElementText->Draw();
	}
}

void Level::AddActor(Actor* actor)
{
	actors.push_back(actor);
}

void Level::AddElement(UIElement* element)
{
	uiElements.push_back(element);
}

void Level::AddTextElement(UIElementText* textElement)
{
	uiTextElements.push_back(textElement);
}

void Level::RemoveActor()
{
	for (auto it = actors.begin(); it != actors.end(); ) {
		if ((*it)->isPendingKill == true) {
			delete* it;       // 1. Delete the object from memory
			it = actors.erase(it); // 2. Remove the hole from the vector safely
		}
		else {
			++it;
		}
	}
}

void Level::RemoveTextElement()
{
	for (auto it = uiTextElements.begin(); it != uiTextElements.end(); ) {
		if ((*it)->isPendingKill == true) {
			delete* it;       // 1. Delete the object from memory
			it = uiTextElements.erase(it); // 2. Remove the hole from the vector safely
		}
		else {
			++it;
		}
	}
}

void Level::AddPoints(float pointsToAdd)
{
}

void Level::PlayerTookDamage(float currentHealth, float maxHealth)
{

}

void Level::PlayerDied(float livesRemaining)
{

}

void Level::ResetPoints()
{
}
