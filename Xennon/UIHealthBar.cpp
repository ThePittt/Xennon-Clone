#include "pch.h"
#include "UIHealthBar.h"
#include <iostream>

UIHealthBar::UIHealthBar(Renderer* renderer, const glm::vec2& position, const glm::vec2& size)
    : UIElement(renderer), size(size), currentHealth(100.0f), maxHealth(100.0f)
{
    this->position = position;
    barTextureHandle = renderer->LoadTexture("graphics/PCFLogo2.bmp",false);
    rect = { 0, 0, renderer->GetTextureWidth(barTextureHandle), renderer->GetTextureHeight(barTextureHandle) };
}

void UIHealthBar::SetHealth(float current, float max) {
    currentHealth = current;
    maxHealth = max;
}

glm::vec3 UIHealthBar::GetHealthColor() const {
    float currentHealthPercent = currentHealth / maxHealth;
   
    if (currentHealthPercent <= 0.33f) {
        return glm::vec3(1.0f, 0.0f, 0.0f); // Red
    }
    else if (currentHealthPercent <= 0.66f) {
        return glm::vec3(1.0f, 1.0f, 0.0f); // Yellow
    }
    else {
        return glm::vec3(0.0f, 1.0f, 0.0f); // Green
    }
}

void UIHealthBar::Draw() {
    if (!visible) return;

    float healthPercent = glm::clamp(currentHealth / maxHealth, 0.0f, 1.0f);

    glm::vec3 color = GetHealthColor();
    glm::vec4 healthColorVec = glm::vec4(color.r, color.g, color.b, 1.0f);
    glm::vec4 backgroundColorVec = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

    renderer->DrawTexture(
        barTextureHandle,
        glm::vec2(position.x - 15, position.y - 5),
        glm::vec2((size.x * 1.1), (size.y * 1.2)),
        0.0f,
        glm::vec4(0, 0, 1, 1),
        true,          
        backgroundColorVec    
    );
    renderer->DrawTexture(
        barTextureHandle,position
        ,
        glm::vec2((size.x * healthPercent), size.y), // Scale width
        0.0f,
        glm::vec4(0, 0, healthPercent, 1), // Crop UVs so it doesn't squash
        true,           // useSolidColor = YES
        healthColorVec  // The color to use
    );

    /*std::cout << "Drawing health bar: " << currentHealth << "/" << maxHealth
        << " (" << (healthPercent * 100) << "%)" << std::endl;*/
}