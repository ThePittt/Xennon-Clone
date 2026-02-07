#pragma once
#include "Renderer.h"
#include <glm/glm.hpp>

class UIElement {
public:
    UIElement(Renderer* renderer) : renderer(renderer), visible(true) {}
    virtual ~UIElement() = default;

    virtual void Update(float deltaTime) {}
    virtual void Draw() = 0;

    void SetPosition(const glm::vec2& pos) { position = pos; }
    void SetVisible(bool vis) { visible = vis; }

protected:
    Renderer* renderer;
    glm::vec2 position;
    bool visible;
};