#include "MirageEngine.h"
#if defined(MIRAGE_PLATFORM_LINUX)

#include "RenderOGL4.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include "SDL2/SDL_opengl.h"

using namespace std;

namespace Mirage {
	namespace Render {

		RenderOGL4::RenderOGL4(int iScreenWidth, int iScreenHeight, void* pWindowHandle)
			:Render(iScreenWidth, iScreenHeight, pWindowHandle){				
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

			PrepareResource();
		}

		RenderOGL4::~RenderOGL4()
		{

		}

		void RenderOGL4::OnSetClearColor()
		{

		}
		void RenderOGL4::PrepareResource()
		{
			const float tem = 2.5;
			const GLfloat positions[] = 
			{
				tem, tem, -tem,
				tem, -tem, -tem,
				-tem, -tem, -tem,
				-tem, tem, -tem,
				-tem, tem, tem,
				-tem, -tem, tem,
				tem, -tem, tem,
				tem, tem, tem
			};
			const GLfloat colors[] = 
			{
				1,0,0,
				1,1,0,
				1,0,1,
				1,1,0,
				1,0,1,
				1,1,0,
				1,0,1,
				0,1,1
			};
			const GLushort indices[] =
			{
				0,1,2,
				0,2,3,
				0,3,7,
				3,4,7,
				7,5,4,
				7,6,5,
				6,1,2,
				6,2,5,
				3,2,5,
				4,3,5,
				0,7,6,
				0,6,1
			};

			GLuint buffer;
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions)+sizeof(colors)+sizeof(indices), nullptr, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions)+sizeof(colors), sizeof(indices), indices);

			glVertexPointer(3, GL_FLOAT, 0, 0);
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