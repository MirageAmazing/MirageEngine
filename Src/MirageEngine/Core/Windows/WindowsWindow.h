#include <memory>
#include "../BasePlatform/BaseWindow.h"
#include "../../Render/RenderSystem.h"
#include "SDL2/SDL.h"
#include "SDL2\SDL_syswm.h"

namespace Mirage {
	namespace Application {
		using namespace Mirage::Render;

		class WindowsApplication;
		typedef SDL_Window* SDL_HWindow;

		// Windows window
		class WindowsWindow :public BaseWindow
		{
		public:
			static std::unique_ptr<WindowsWindow> Get(CStyleStr name, uint32 positionX, uint32 positionY, uint32 w, uint32 h) {
				auto windows = std::make_unique<WindowsApplication>();
			}

		public:
			~WindowsWindow() {
				SDL_DestroyWindow(mWindow);
			};

			virtual void Tick() override{

				SDL_Event event;
				if (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_EventType::SDL_QUIT:
						mIsQuit = true;
						break;
					default:
						break;
					}
				}

			}

		private:
			WindowsWindow(CStyleStr name, uint32 positionX, uint32 positionY, uint32 w, uint32 h) {
				SDL_Window *window = 0;

				SDL_Init(SDL_INIT_VIDEO);
				window = SDL_CreateWindow(name, positionX, positionY, w, h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

				SDL_SysWMinfo wmInfo;
				SDL_VERSION(&wmInfo.version);
				SDL_GetWindowWMInfo((SDL_Window*)window, &wmInfo);
				mHWND = wmInfo.info.win.window;

				mRender = RenderSystem::GetInstance()->CreateRender(RenderType::DirectX11, w, h, mWindow);
			};

		private:
			RenderPtr mRender;

			HWND mHWND;
			SDL_HWindow mWindow;
			WindowsApplication* mOwnerApp;
		};

	}
}