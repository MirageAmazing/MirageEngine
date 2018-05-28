#include "BaseRender.h"
#include "../RenderDX11/RenderDX11.h"
#include "../RenderOGL4/RenderOGL4.h"

namespace Mirage {
	namespace Render {
		unique_ptr<Render> Render::mBaseRender = nullptr;

		unique_ptr<Render> Render::GetRender(RenderType type, int iScreenWidth, int iScreenHeight, void* pWindowHandle)
		{
			switch (type)
			{
#if defined(MIRAGE_PLATFORM_WINDOWS)
			case RenderType::DirectX11:
				if (mBaseRender == nullptr)
					mBaseRender = unique_ptr<Render>(new RenderDX11(iScreenWidth, iScreenHeight, pWindowHandle));
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

		Render::Render(int iScreenWidth, int iScreenHeight, void* pWindowHandle)
		{
			mRenderWidth = iScreenWidth;
			mRenderHeight = iScreenHeight;
			mWindowHandle = pWindowHandle;
		}

		Render::Render(Render&& render)
		{
			mWindowHandle = render.mWindowHandle;
			mClearColor[0] = render.mClearColor[0];
			mClearColor[1] = render.mClearColor[1];
			mClearColor[2] = render.mClearColor[2];
		}

		Render::~Render()
		{
		}

		bool Render::EnvirmentCheck()
		{
			return true;
		}

		void Render::SetClearColor(float r, float g, float b){
			mClearColor[0] = r;
			mClearColor[1] = g;
			mClearColor[2] = b;

			this->OnSetClearColor();
		}

		void Render::SetFullScreen(bool value){
			mFullScreen = value;
		}

		void Render::SetVsyncEnable(bool value){
			mVsyncEnabled = value;
		}

		void Render::OnSetClearColor(){
		}

		void Render::Frame(){

		}
	}
}