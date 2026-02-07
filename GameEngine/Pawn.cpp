#include "pch.h"
#include "Pawn.h"
#include <iostream>


Pawn::Pawn(const std::string& path, Renderer* rend, int screenW, int screenH, Level* level)
    : Actor(path, rend, screenW, screenH, level), movementSpeed(500.0f), gamepad(nullptr)
    , gamepadID(0)
    , deadzone(0.2f)
{
    OpenGamepad(0);
}

Pawn::~Pawn()
{
    CloseGamepad();
}

void Pawn::SetSpeed(float speed) {
    movementSpeed = speed;
}

void Pawn::Update(float deltaTime) {
    // 1. Get Keyboard State
    Actor::Update(deltaTime);

    movingFoward = false;
    movingBackwards = false;
    movingLeft = false;
    movingRight = false;
    playerShoot = false;


    const bool* keys = SDL_GetKeyboardState(nullptr);
    float gamepadAxisX = 0.0f;
    float gamepadAxisY = 0.0f;


    if (gamepad) {
         gamepadAxisX = SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_LEFTX) / 32768.0f;
         gamepadAxisY = SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_LEFTY) / 32768.0f;

    }

    // 2. Move based on keys
    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP] || gamepadAxisY < -deadzone) {

        if (positionSize.y >= (positionSize.h/2)) {

            positionSize.y -= movementSpeed * deltaTime;

            movingFoward = true;
            movingBackwards = false;
            movingLeft = false;
            movingRight = false;
        }
        
    }
    else if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN] || gamepadAxisY > deadzone) {

        if (positionSize.y <= ( screenHeight - (positionSize.h/2))) {

            positionSize.y += movementSpeed * deltaTime;

            movingFoward = false;
            movingBackwards = true;
            movingLeft = false;
            movingRight = false;
        }

    }
    else if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT] || gamepadAxisX < -deadzone) {

        if (positionSize.x >= (positionSize.w/2)) {
            positionSize.x -= movementSpeed * deltaTime;

            movingFoward = false;
            movingBackwards = false;
            movingLeft = true;
            movingRight = false;
        }
        

    }
    else if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT] || gamepadAxisX > deadzone) {

        if (positionSize.x <= (screenWidth - (positionSize.w / 2))) {
            positionSize.x += movementSpeed * deltaTime;

            movingFoward = false;
            movingBackwards = false;
            movingLeft = false;
            movingRight = true;
        }
        
    }

    if (keys[SDL_SCANCODE_SPACE] || SDL_GetGamepadButton(gamepad, SDL_GAMEPAD_BUTTON_SOUTH))
    {
        playerShoot = true;
    }

}


void Pawn::OpenGamepad(int deviceIndex)
{
    int numGamepads = 0;
    SDL_JoystickID* joysticks = SDL_GetGamepads(&numGamepads);

    if (joysticks && deviceIndex < numGamepads) {
        SDL_JoystickID joystickID = joysticks[deviceIndex];

        if (SDL_IsGamepad(joystickID)) {
            gamepad = SDL_OpenGamepad(joystickID);

            if (gamepad != nullptr) {
                gamepadID = joystickID;
                const char* name = SDL_GetGamepadName(gamepad);
                char* mapping = SDL_GetGamepadMapping(gamepad);

                std::cout << "Gamepad connected: "
                    << (name ? name : "Unknown") << std::endl;

                if (mapping) {
                    std::cout << "Mapping: " << mapping << std::endl;
                    SDL_free(mapping);
                }
            }
        }
    }
    SDL_free(joysticks);
   
}

void Pawn::CloseGamepad()
{
    if (gamepad) {
        SDL_CloseGamepad(gamepad);
        gamepad = nullptr;
        gamepadID = 0;
    }
}