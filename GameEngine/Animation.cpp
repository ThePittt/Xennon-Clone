#include "pch.h"
#include "Animation.h"


Animation::Animation() : frameWidth(1), frameHeight(1), currentFrameWidth(0), currentFrameHeight(0), frameTime(0), switchTime(0.05f), currentFrame(0) {}

void Animation::Setup(std::vector<int> animframes, int textureWidth, int textureHeight, bool isLoopable) {

    animationLoopable = isLoopable;
    frames.clear();

    for (int anim : animframes) {
        if (anim >= textureWidth) {
            int tempFrame;
            int heightValue;
            
            heightValue = anim / textureWidth;

            tempFrame = anim - (textureWidth * heightValue);

            frames.push_back({tempFrame, heightValue});
        }
        else {
            frames.push_back({ anim, 0 });
        }
        
    }

    vectorSize = frames.size();
    --vectorSize;
}

void Animation::Update(float deltaTime) {

    frameTime += deltaTime;

    if (frameTime >= switchTime) {
        frameTime = 0;
        currentFrameWidth = frames.at(currentFrame).width;
        currentFrameHeight = frames.at(currentFrame).height;
        

        if (currentFrame == vectorSize) {
            if (animationLoopable) {
                currentFrame = 0;
            }
            else {
                animationEnded = true;
            }
        }
        else {
            ++currentFrame;
            animationEnded = false;
        }
              
    }
}

glm::vec4 Animation::GetCurrentFrameRect(float textureWidth, float textureHeight, float frameW, float frameH) {

    float x = currentFrameWidth * frameW;
    float y = currentFrameHeight * frameH;

    float u1 = x / textureWidth;                      // Left
    float v1 = y / textureHeight;                     // Top
    float u2 = (x + frameW) / textureWidth;  // Right
    float v2 = (y + frameH) / textureHeight;// Bottom
    return { u1, v1, u2, v2 };
}