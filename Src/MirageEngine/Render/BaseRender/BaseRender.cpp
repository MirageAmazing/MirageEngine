#include "BaseRender.h"
#include "../RenderDX11/RenderDX11.h"
#include "../RenderOGL4/RenderOGL4.h"

namespace Mirage {
	namespace Render {
		unique_ptr<BaseRender> BaseRender::mBaseRender = nullptr;

		unique_ptr<BaseRender> BaseRender::GetRender(RenderType type, int iScreenWidth, int iScreenHeight, void* pWindowHandle)
		{
			switch (type)
			{
#if defined(MIRAGE_PLATFORM_WINDOWS)
			case RenderType::DirectX11:
				if (mBaseRender == nullptr)
					mBaseRender = unique_ptr<BaseRender>(new RenderDX11(iScreenWidth, iScreenHeight, pWindowHandle));
				return move(mBaseRender);
#endif
#if defined(MIRAGE_PLATFORM_LINUX)
			case RenderType::OpenGL40:
				if (mBaseRender == nullptr)
					mBaseRender = unique_ptr<BaseRender>(new RenderOGL4(iScreenWidth, iScreenHeight, pWindowHandle));
				return move(mBaseRender);
#endif
			}

			return nullptr;
		}

		BaseRender::BaseRender(int iScreenWidth, int iScreenHeight, void* pWindowHandle)
		{
			mRenderWidth = iScreenWidth;
			mRenderHeight = iScreenHeight;
			mWindowHandle = pWindowHandle;
		}

		BaseRender::BaseRender(BaseRender&& render)
		{
			mWindowHandle = render.mWindowHandle;
			mClearColor[0] = render.mClearColor[0];
			mClearColor[1] = render.mClearColor[1];
			mClearColor[2] = render.mClearColor[2];
		}

		BaseRender::~BaseRender()
		{
		}

		bool BaseRender::EnvirmentCheck()
		{
			return true;
		}

		void BaseRender::SetClearColor(float r, float g, float b){
			mClearColor[0] = r;
			mClearColor[1] = g;
			mClearColor[2] = b;

			this->OnSetClearColor();
		}

		void BaseRender::SetFullScreen(bool value){
			mFullScreen = value;
		}

		void BaseRender::SetVsyncEnable(bool value){
			mVsyncEnabled = value;
		}

		void BaseRender::OnSetClearColor(){
		}

		void BaseRender::Frame(){

		}
	}
}