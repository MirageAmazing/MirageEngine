#pragma once
#include "MirageEngine.h"

#if defined(MIRAGE_PLATFORM_WINDOWS)
#define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "../Render/Render.h"
#include "../RenderOGL4/ShaderOGL4.h"
#include "../Core/Math/Camera.h"
#include "../Core/Math/Transform.h"

#if defined(MIRAGE_PLATFORM_LINUX)
#pragma comment(lib, "libGLEW.a")
#endif

namespace Mirage {
	namespace Render {

		using namespace Mirage::Math;

		class RenderOGL4 :public Render{
		public:
			RenderOGL4(int iScreenWidth, int iScreenHeight, void* pWindowHandle);
			~RenderOGL4();
						
			void Frame() override;
			ShaderComplieResult_Ptr LoadOrComplieShader(string source, ShaderType type) override;

			GLuint LoadShaders(const char* vs, const char* ps);
			void PrepareResource();
			
		protected:
			void OnSetClearColor() override;

			//<--------------------Temp
			GLuint mProgramID;
			GLuint mBufferID;
			GLuint mVertexBufferID;
			GLuint mColorBufferID;
			GLuint mIndexBufferID;
			GLfloat mVertex = 0;
			GLuint mMatrixID;
			std::unique_ptr<Camera> mCamera;
			Transform mTransform;
			bool mSwitch = true;
			//Temp-------------------->

			SDL_Window* mWindow;
		};
	}
}
