#pragma once

#include <glm/glm.hpp>
#include <SDL3/SDL_rect.h>
#include <vector>

struct Vector2{
    int width;
    int height;
};

class Animation
{
    int currentFrame;
    int currentFrameWidth;
    int currentFrameHeight;
    int frameWidth;
    int frameHeight;
    float frameTime;
    float switchTime;
    std::vector<Vector2> frames;
    bool animationLoopable = false;
    int vectorSize;

public:

    Animation();
    void Setup(std::vector<int> animframes, int textureWidth, int textureHeight, bool isLoopable);
    void Update(float deltaTime);
    glm::vec4 GetCurrentFrameRect(float textureWidth, float textureHeight, float frameW, float frameH);

    bool animationEnded = false;
};

