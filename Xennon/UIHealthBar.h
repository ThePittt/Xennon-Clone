#pragma once
#include "UIElement.h"

class UIHealthBar : public UIElement {
public:
    UIHealthBar(Renderer* renderer,  const glm::vec2& position, const glm::vec2& size);

    void SetHealth(float current, float max);
    void Draw() override;

private:
    glm::vec2 size;
    float currentHealth;
    float maxHealth;
    float healthPercent;
    SDL_FRect rect;
    int barTextureHandle;

    glm::vec3 GetHealthColor() const;
};
