#pragma once
#include "Actor.h"
class Pawn : public Actor {

	float movementSpeed;

protected:

	bool movingRight = false;
	bool movingLeft = false;
	bool movingFoward = false;
	bool movingBackwards = false;
	bool playerShoot = false;


	SDL_Gamepad* gamepad;
	SDL_JoystickID gamepadID;
	SDL_Event inputEvent;
	float deadzone = 0.1f; // Analog stick deadzone

public:
	Pawn(const std::string& texturePath, Renderer* renderer, int screenW, int screenH, Level* level);
	~Pawn();
	// Override Update so we can check for input every frame
	void Update(float deltaTime) override;

	// Set how fast the ship moves
	void SetSpeed(float speed);

	void OpenGamepad(int deviceIndex = 0);
	void CloseGamepad();
	void SetDeadzone(float dz) { deadzone = dz; }
	bool HasGamepad() const { return gamepad != nullptr; }
};

