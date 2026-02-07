#include "pch.h"
#include "Actor.h"
#include "Level.h"
#include <iostream>
#include <iomanip>

void Actor::SpawnActor(Actor* actor)
{
	if (currentLevel) {
		currentLevel->AddActor(actor);
	}
}

void Actor::AddScore(int scoreToAdd)
{
	if (currentLevel) {

	}
}

void Actor::DestroyActor()
{
	isPendingKill = true;
}

Actor::Actor(const std::string& path, Renderer* rend, int screenW, int screenH, Level* level) {
	renderer = rend;
	textureHandle = renderer->LoadTexture(path, true);
	currentLevel = level;
	screenWidth = screenW;
	screenHeight = screenH;
	positionSize = { 0, 0, (float)screenWidth, (float)screenHeight };
	rect = { 0, 0, renderer->GetTextureWidth(textureHandle), renderer->GetTextureHeight(textureHandle) };
	bodyID = b2_nullBodyId;
	bodyRotation = b2MakeRot(0.0f);
}

Actor::~Actor()
{
	if (B2_IS_NON_NULL(bodyID))
	{
		b2DestroyBody(bodyID);
		bodyID = b2_nullBodyId;
	}
}

void Actor::SetSprite(int width, int height, bool hasAnimation, std::vector<int> animframes, bool isLoopable)
{
	frameWidth = renderer->GetTextureWidth(textureHandle) / width;
	frameHeight = renderer->GetTextureHeight(textureHandle) / height;

	if (animframes.at(0) > width) {
		int temp = animframes.at(0) / width;
		rect.y = temp * frameHeight;
		rect.x = (animframes.at(0) - (width * temp)) * frameWidth;

	}
	else {
		rect.x = animframes.at(0) * frameWidth;
		rect.y = 0;

	}

	rect.w = frameWidth;
	rect.h = frameHeight;

	useAnimation = hasAnimation;

	if (useAnimation) {
		animation.Setup(animframes, width, height, isLoopable);
	}

}

void Actor::SetNewAnimation(std::vector<int> animframes, int width, int height, bool isLoopable)
{
	if (useAnimation) {
		animation.Setup(animframes, width, height, isLoopable);
	}
}

void Actor::SetPosition(int x, int y) {
	positionSize.x = x;
	positionSize.y = y;
}

void Actor::SetScale(float w, float h) {
	positionSize.w = frameWidth * w;
	positionSize.h = frameHeight * h;
}

void Actor::Update(float deltaTime) {


	if (useAnimation) {
		animation.Update(deltaTime);
		hasAnimationEnded = animation.animationEnded;
	}
}

void Actor::UpdateRigidbodies()
{
	if (B2_IS_NON_NULL(bodyID)) {
		// Convert pixels to meters (Box2D works in meters)
		const float PIXELS_TO_METERS = 1.0f / 64.0f; // Adjust this scale as needed

		b2Vec2 metersPos = {
			positionSize.x * PIXELS_TO_METERS ,
			positionSize.y  * PIXELS_TO_METERS
		};

		b2Body_SetTransform(bodyID, metersPos, bodyRotation);
	}
	//// Get body position and rotation
	//b2Vec2 position = b2Body_GetPosition(bodyID);
	//b2Rot rotation = b2Body_GetRotation(bodyID);
	//float angle = b2Rot_GetAngle(rotation);

	//std::cout << std::fixed << std::setprecision(2) << bodyID.index1 << ""
	//	<< position.x << " "
	//	<< position.y << " "
	//	<< angle << std::endl;
}

void Actor::Render(Renderer* rend) {
	SDL_FRect src;
	glm::vec4 uvCoords;
	float renderX = positionSize.x - (positionSize.w / 2.0f);
	float renderY = positionSize.y - (positionSize.h / 2.0f);
	if (useAnimation) {
		uvCoords = animation.GetCurrentFrameRect(renderer->GetTextureWidth(textureHandle),
			renderer->GetTextureHeight(textureHandle), frameWidth, frameHeight);


		renderer->DrawTexture(textureHandle, glm::vec2(renderX, renderY), // Position
			glm::vec2(positionSize.w, positionSize.h), // Scale
			rotation,                                      // Rotation
			uvCoords);
	}
	else {
		src = rect;



		float texW = rend->GetTextureWidth(textureHandle);
		float texH = rend->GetTextureHeight(textureHandle);

		//glm::vec4 uvCoords;
		uvCoords.x = src.x / texW;              // U Inicial (Esquerda) -> vai para o .x do vec4
		uvCoords.y = src.y / texH;              // V Inicial (Topo)     -> vai para o .y do vec4
		uvCoords.z = (src.x + src.w) / texW;    // U Final (Direita)    -> vai para o .z do vec4
		uvCoords.w = (src.y + src.h) / texH;    // V Final (Fundo)      -> vai para o .w do vec4

		renderer->DrawTexture(textureHandle, glm::vec2(renderX, renderY), // Position
			glm::vec2(positionSize.w, positionSize.h), // Scale
			rotation,                                      // Rotation
			uvCoords);
	}

}

void Actor::CreateRigidBody(ActorType type, CollisionCategory category, std::initializer_list<CollisionCategory> maskCategories)
{
	const float PIXELS_TO_METERS = 1.0f / 64.0f;

	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	actorType = type;
	bodyDef.enableSleep = false;
	// Set initial position in meters
	bodyDef.position = b2Vec2{
		positionSize.x * PIXELS_TO_METERS,
		positionSize.y * PIXELS_TO_METERS
	};

	b2BodyId bodyId = b2CreateBody(currentLevel->worldId, &bodyDef);
	bodyID = bodyId;

	float angleRad = 0.0f;
	b2Rot rot;
	rot.s = sinf(angleRad);
	rot.c = cosf(angleRad);
	bodyRotation = rot;

	// Create box in meters (convert from pixels)
	b2Polygon dynamicBox = b2MakeBox(
		(positionSize.w * PIXELS_TO_METERS) / 2.0f,  // Box2D wants half-widths
		(positionSize.h * PIXELS_TO_METERS) / 2.0f
	);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.material.friction = 0.0f;
	shapeDef.filter.categoryBits = category;

	uint64_t combinedMask = 0;
	for (CollisionCategory maskCat : maskCategories) {
		combinedMask |= static_cast<uint64_t>(maskCat);
	}
	shapeDef.filter.maskBits = combinedMask;
	shapeDef.enableContactEvents = true;
	//shapeDef.isSensor = true;


	shapeDef.userData = this;  // This is what you're retrieving in PhysicsCollisions


	b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

	//b2Filter filter = b2Shape_GetFilter(shapeId);
	//std::cout << "VERIFIED Filter - Category: 0x" << std::hex << filter.categoryBits
	//	<< ", Mask: 0x" << filter.maskBits << std::dec << std::endl;

	//// Check if contacts are enabled
	//bool contactsEnabled = b2Shape_AreContactEventsEnabled(shapeId);
	//std::cout << "Contact events enabled: " << (contactsEnabled ? "YES" : "NO") << std::endl;
}
void Actor::OnCollisionBegin(Actor* actor)
{
	std::cout << "Hit" << std::endl;
}
void Actor::SyncFromPhysics()
{
	if (B2_IS_NON_NULL(bodyID)) {
		const float METERS_TO_PIXELS = 64.0f; // Inverse of PIXELS_TO_METERS

		b2Vec2 position = b2Body_GetPosition(bodyID);
		b2Rot rotation = b2Body_GetRotation(bodyID);

		// Update rendering position from physics
		positionSize.x = position.x * METERS_TO_PIXELS;
		positionSize.y = position.y * METERS_TO_PIXELS;


		bodyRotation = rotation;
	}
}
void Actor::TakeDamage(float damage) {
	health -= damage;
}