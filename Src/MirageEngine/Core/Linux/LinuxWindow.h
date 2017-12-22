#pragma once 

#include "../BasePlatform/BaseWindow.h"

#include "SDL2/SDL.h"

typedef SDL_Window* SDL_HWindow;

class LinuxWindow:public BaseWindow
{
public:
    ~LinuxWindow();

private:
    LinuxWindow();

private:
    SDL_HWindow mHWND;
    
};