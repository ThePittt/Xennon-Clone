#include "pch.h"
#include "UILifeCounter.h"

UILifeCounter::UILifeCounter(Renderer* renderer, const std::string& lifeIconPath,
    const glm::vec2& position)
    : UIElement(renderer), currentLives(3), iconSize(64, 64), spacing(30.0f)
{
    this->position = position;
    lifeIconHandle = renderer->LoadTexture(lifeIconPath, true);
}

void UILifeCounter::SetLives(int lives) {
    currentLives = lives;
}

void UILifeCounter::Draw() {
    if (!visible) return;

    for (int i = 0; i < currentLives; i++) {
        glm::vec2 iconPos = position + glm::vec2((iconSize.x + spacing) * i, 0);

        renderer->DrawTexture(
            lifeIconHandle,
            iconPos,
            iconSize,
            0.0f,
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) // Full texture
        );
    }
}