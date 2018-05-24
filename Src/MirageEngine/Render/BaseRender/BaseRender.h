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

		class BaseRender
		{
		public:
			BaseRender(int iScreenWidth, int iScreenHeight, void* pWindowHandle);
			BaseRender(BaseRender&& render);
			virtual ~BaseRender();
			BaseRender(BaseRender&) = delete;

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
			static unique_ptr<BaseRender> GetRender(RenderType type, int iScreenWidth, int iScreenHeight, void* pWindowHandle);

		private:
			static unique_ptr<BaseRender> mBaseRender;
		};
	}
}
