#pragma once

#include <memory>
#include <string>
#include "../../Core/HAL/Platform.h"
#include "Shader.h"
using namespace std;

namespace Mirage {
	namespace Render {
		enum RenderType
		{
			DirectX11,
			OpenGL40
		};

		class Render
		{
		public:
			Render(int iScreenWidth, int iScreenHeight, void* pWindowHandle, RenderType renderType);
			Render(Render&& render);
			virtual ~Render();
			Render(Render&) = delete;

			virtual void Frame();

			RenderType GetRenderType();
			void SetClearColor(float r, float g, float b);
			void SetFullScreen(bool value);
			void SetVsyncEnable(bool value);

			template<class T>
			void SetShader(FromShaderType(T) shader) {}

			virtual void DrawIndex() {};
			virtual void DrawInstance() {};

			virtual ShaderComplieResult_Ptr LoadOrComplieShader(string source, ShaderType type);

		protected:
			virtual bool EnvirmentCheck();
			virtual void OnSetClearColor();

		protected:
			int mRenderWidth = 800;
			int mRenderHeight = 600;
			float mClearColor[3]{ 0,0,0 };
			void* mWindowHandle;
			bool mFullScreen = false;
			bool mVsyncEnabled = false;
			int mVideoCardMemory = 0;
			RenderType mRenderType;
		
		private:
			static unique_ptr<Render> mRender;
		};

		using RenderPtr = shared_ptr<Render>;
	}
}
