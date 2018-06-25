#pragma once 
#include "MirageEngine.h"
#if defined(MIRAGE_PLATFORM_LINUX)

#include <memory>
#include "../BasePlatform/BaseWindow.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"

namespace Mirage {
	namespace Application {

		class LinuxApplication;
		typedef SDL_Window* SDL_HWindow;

		class LinuxWindow :public BaseWindow
		{
		public:
			static std::unique_ptr<LinuxWindow> Make(LinuxApplication* owner, CStyleStr name, uint32 locationX, uint32 locationY, uint32 w, uint32 h){
				auto window = std::unique_ptr<LinuxWindow>(new LinuxWindow(owner, name, locationX, locationY, w, h));
				return window;
			}

		public:	
			LinuxWindow(LinuxApplication* owner, CStyleStr name, uint32 locationX, uint32 locationY, uint32 w, uint32 h) {
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
				
				SDL_Init(SDL_INIT_VIDEO);
				mWindow = SDL_CreateWindow(name, locationX, locationY, w, h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

				SDL_SysWMinfo wmInfo;
				SDL_VERSION(&wmInfo.version);
				SDL_GetWindowWMInfo(mWindow, &wmInfo);
				mX11Handle = wmInfo.info.x11.window;
				
				mOwnerApp = owner;
				mLocationX = locationX;
				mLocationY = locationY;
				mWidth = w;
				mHeight = h;
			};
			~LinuxWindow() {

			};

			virtual void Tick() override{
				SDL_Event event;
				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_EventType::SDL_QUIT:
						mIsQuit = true;
						break;
					default:
						break;
					}
				}
			}
			
			SDL_Window* GetWindowHandle(){
				return mWindow;
			}

		private:
			SDL_Window* mWindow;
			Window mX11Handle;
			LinuxApplication* mOwnerApp;
		};
	}
}

#endif