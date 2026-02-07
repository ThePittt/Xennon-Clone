#pragma once
#include "UIElement.h"

class UILifeCounter : public UIElement {
public:
    UILifeCounter(Renderer* renderer, const std::string& lifeIconPath,
        const glm::vec2& position);

    void SetLives(int lives);
    void Draw() override;

private:

    int currentLives;
    int lifeIconHandle;
    glm::vec2 iconSize;
    float spacing;
};