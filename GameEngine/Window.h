#pragma once
#include <string>
#include <memory>

#include "SDL3/SDL.h"

class Window
{
    SDL_Window* window;
    int width, height;

public:

    Window(std::string title, int Width, int Height);
    ~Window();
    SDL_Window* GetNativeWindow() const { return window; };
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
};

