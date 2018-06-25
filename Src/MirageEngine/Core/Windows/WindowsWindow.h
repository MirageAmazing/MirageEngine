#include "MirageEngine.h"
#if defined(MIRAGE_PLATFORM_WINDOWS)

#include <memory>
#include "../BasePlatform/BaseWindow.h"
#include "../../Render/RenderSystem.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"

namespace Mirage {
	namespace Application {
		
		using namespace Mirage::Render;

		class WindowsApplication;
		typedef SDL_Window* SDL_HWindow;

		// Windows window
		class WindowsWindow :public BaseWindow
		{
		public:
			static std::unique_ptr<WindowsWindow> Make(WindowsApplication* owner, CStyleStr name, uint32 locationX, uint32 locationY, uint32 w, uint32 h, RenderType renderType) {
				auto windows = std::make_unique<WindowsWindow>(owner, name, locationX, locationY, w, h, renderType);
				return windows;
			}

		public:
			WindowsWindow(WindowsApplication* owner, CStyleStr name, uint32 locationX, uint32 locationY, uint32 w, uint32 h, RenderType renderType) {
				mRenderType = renderType;
				SDL_Init(SDL_INIT_VIDEO);

				mWindow = SDL_CreateWindow(name, locationX, locationY, w, h, 
					(mRenderType == RenderType::OpenGL40 ? SDL_WINDOW_OPENGL: SDL_WINDOW_SHOWN) | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

				SDL_SysWMinfo wmInfo;
				SDL_VERSION(&wmInfo.version);
				SDL_GetWindowWMInfo((SDL_Window*)mWindow, &wmInfo);

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
			SDL_HWindow GetWindowHandle() {
				return mWindow;
			}

		private:
			
		private:
			RenderType mRenderType;

			HWND mHWND;
			SDL_HWindow mWindow;
			WindowsApplication* mOwnerApp;
		};

	}
}

#endif