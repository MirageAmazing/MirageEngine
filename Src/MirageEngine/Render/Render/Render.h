#pragma once

#include <memory>
#include "../../Core/HAL/Platform.h"
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
			Render(int iScreenWidth, int iScreenHeight, void* pWindowHandle);
			Render(Render&& render);
			virtual ~Render();
			Render(Render&) = delete;

			void SetClearColor(float r, float g, float b);
			void SetFullScreen(bool value);
			void SetVsyncEnable(bool value);

			virtual void Frame();

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

		public:
			static unique_ptr<Render> GetRender(RenderType type, int iScreenWidth, int iScreenHeight, void* pWindowHandle);

		private:
			static unique_ptr<Render> mRender;
		};

		using RenderPtr = shared_ptr<Render>;
	}
}
