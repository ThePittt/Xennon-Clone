#include "pch.h"
#include "Window.h"

#include "SDL3/SDL.h"


Window::Window(std::string title, int Width, int Height)
{
    width = Width;
    height = Height;
    SDL_Init(SDL_INIT_VIDEO);

    if ((Width == 1920 || Width == 1280 || Width == 640) && (Height == 1080 || Height == 720 || Height == 480)) {
        window = SDL_CreateWindow(title.c_str(), Width, Height, SDL_WINDOW_OPENGL);
    }
    else {
        window = SDL_CreateWindow(title.c_str(), 1920, 1080, SDL_WINDOW_OPENGL);
    }
}


Window::~Window()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}



