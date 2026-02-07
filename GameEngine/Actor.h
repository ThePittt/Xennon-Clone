#pragma once
#include "Animation.h"
#include "Renderer.h"
#include <glm/glm.hpp>
#include <vector>
#include "box2d/box2d.h"

class Level;

enum CollisionCategory : uint64_t {
	CATEGORY_NONE = 0,  // 0
	CATEGORY_PLAYER = 1 << 0,  // 1
	CATEGORY_ENEMY = 1 << 1,  // 2
	CATEGORY_PLAYER_MISSILE = 1 << 2,  // 4
	CATEGORY_ENEMY_MISSILE = 1 << 3, // 8
	CATEGORY_POWERUP = 1 << 4,  // 16
	CATEGORY_COMPANION = 1 << 5 // 32 // 8
};

// Actor type enum for easier type checking
enum  class ActorType {
	NONE,
	PLAYER,
	ENEMY,
	PLAYER_MISSILE,
	ENEMY_MISSILE,
	POWERUP_SHIELD,
	POWERUP_WEAPON,
	POWERUP_COMPANION,
};

class Actor
{
protected:
	Renderer* renderer;
	Level* currentLevel;
	SDL_FRect positionSize;
	SDL_FRect rect;
	Animation animation;
	bool useAnimation = false;
	float animFrameWidth = 0;
	float animFrameHeight = 0;

	float frameWidth = 0;
	float frameHeight = 0;
	int screenWidth;
	int screenHeight;

	int textureHandle;
	int rotation = 90;
	//Collisions
	b2BodyId bodyID;
	b2Rot bodyRotation;

	ActorType actorType = ActorType::NONE;

	void SpawnActor(Actor* actor);
	void AddScore(int scoreToAdd);

	int health = 1;
public:
	Actor(const std::string& texturePath, Renderer* renderer, int screenW, int screenH, Level* level);
	virtual ~Actor();

	virtual void Update(float deltaTime);
	void UpdateRigidbodies();
	virtual void Render(Renderer* renderer);

	void SetSprite(int width, int height, bool hasAnimation, std::vector<int> animframes, bool isLoopable);
	void SetNewAnimation(std::vector<int> animframes, int width, int height, bool isLoopable);
	void SetPosition(int x, int y);
	void SetScale(float w, float h);
	SDL_FRect GetBounds() const { return rect; }

	bool isPendingKill = false;
	bool hasAnimationEnded = false;

	void CreateRigidBody(ActorType type, CollisionCategory category, std::initializer_list<CollisionCategory> maskCategories);

	ActorType GetActorType() const { return actorType; }
	b2BodyId GetBodyId() const { return bodyID; }
	virtual void OnCollisionBegin(Actor* actor);
	void DestroyActor();
	void SyncFromPhysics();


	 virtual void TakeDamage(float damage);
};

