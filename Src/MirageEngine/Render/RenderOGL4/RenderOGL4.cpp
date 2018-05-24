#include "RenderOGL4.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include "SDL2/SDL_opengl.h"

using namespace std;

#if defined(MIRAGE_PLATFORM_LINUX)

namespace Mirage {
	namespace Render {
		RenderOGL4::RenderOGL4(int iScreenWidth, int iScreenHeight, void* pWindowHandle)
			:BaseRender(iScreenWidth, iScreenHeight, pWindowHandle){
			mWindow = (SDL_Window*)pWindowHandle;

			SDL_SysWMinfo wmInfo;
			SDL_VERSION(&wmInfo.version);
			SDL_GetWindowWMInfo(mWindow, &wmInfo);
			auto window = wmInfo.info.x11.window;
			auto context = SDL_GL_CreateContext(mWindow);

			if (context == nullptr)
			{
				cout << "OpenGL40 initialization failed!" << endl;
				return;
			}
			else
			{
				cout << "OpenGL40 initialization succeeded!" << endl;
				glewInit();
				glViewport(0, 0, iScreenWidth, iScreenHeight);
			}
		}

		RenderOGL4::~RenderOGL4()
		{

		}

		void RenderOGL4::OnSetClearColor()
		{

		}

		void RenderOGL4::Frame()
		{
			glClearColor(mClearColor[0], mClearColor[1], mClearColor[2], 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glColor3f(1 - mClearColor[0], 1 - mClearColor[1], 1 - mClearColor[2]);

			glBegin(GL_LINE_LOOP);
			glVertex2f(mVertex, mVertex);
			glVertex2f(0.75, 0.25);
			glVertex2f(0.75, 0.75);
			glVertex2f(0.25, 0.75);
			glEnd();

			if (mVertex > 0.35)
				mSwitch = false;
			else if (mVertex < 0)
				mSwitch = true;
			if (mSwitch)
				mVertex += 0.001;
			else
				mVertex -= 0.001;

			SDL_GL_SwapWindow(mWindow);
		}
	}
}

#endif