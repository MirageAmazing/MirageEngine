#pragma once
#include "MirageEngine.h"
#if defined(MIRAGE_PLATFORM_LINUX)

#include "../BaseRender/BaseRender.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#pragma comment(lib, "libGLEW.a")

namespace Mirage {
	namespace Render {
		class RenderOGL4 :public Render{
		public:
			RenderOGL4(int iScreenWidth, int iScreenHeight, void* pWindowHandle);
			~RenderOGL4();

			void Frame() override;

		protected:
			void OnSetClearColor() override;

			GLfloat mVertex = 0;
			bool mSwitch = true;
			SDL_Window* mWindow;
		};
	}
}
#endif