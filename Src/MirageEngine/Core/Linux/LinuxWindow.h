#pragma once 

#include "../BasePlatform/BaseWindow.h"
#include "LinuxApplication.h"

#include "SDL2/SDL.h"

typedef SDL_Window* SDL_HWindow;

class LinuxWindow:public BaseWindow
{
public:
    static LinuxWindow* Get();
    
public:
	~LinuxWindow() {};

private:
	LinuxWindow() {};

private:
    SDL_HWindow mHWND;
    
    LinuxApplication* mOwnerApp;
};