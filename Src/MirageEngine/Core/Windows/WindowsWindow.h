#include "MirageEngine.h"
#if defined(MIRAGE_PLATFORM_WINDOWS)

#include <memory>
#include "../BasePlatform/BaseWindow.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"

namespace Mirage {
	namespace Application {
		
		class WindowsApplication;
		typedef SDL_Window* SDL_HWindow;

		// Windows window
		class WindowsWindow :public BaseWindow
		{
		public:
			static std::unique_ptr<WindowsWindow> Make(WindowsApplication* owner, CStyleStr name, uint32 locationX, uint32 locationY, uint32 w, uint32 h) {
				auto windows = std::make_unique<WindowsWindow>(owner, name, locationX, locationY, w, h);
				return windows;
			}

		public:
			WindowsWindow(WindowsApplication* owner, CStyleStr name, uint32 locationX, uint32 locationY, uint32 w, uint32 h) {
				SDL_Window *window = 0;

				SDL_Init(SDL_INIT_VIDEO);
				window = SDL_CreateWindow(name, locationX, locationY, w, h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

				SDL_SysWMinfo wmInfo;
				SDL_VERSION(&wmInfo.version);
				SDL_GetWindowWMInfo((SDL_Window*)window, &wmInfo);

				mHWND = wmInfo.info.win.window;
				mOwnerApp = owner;
				mLocationX = locationX;
				mLocationY = locationY;
				mWidth = w;
				mHeight = h;
			};
			~WindowsWindow() {
				SDL_DestroyWindow(mWindow);
				SDL_Quit();
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

			HWND GetHWND() {
				return mHWND;
			}

		private:
			
		private:
			
			HWND mHWND;
			SDL_HWindow mWindow;
			WindowsApplication* mOwnerApp;
		};

	}
}

#endif