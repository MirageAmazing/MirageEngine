#include "Render.h"
#include "../RenderDX11/RenderDX11.h"
#include "../RenderOGL4/RenderOGL4.h"

namespace Mirage {
	namespace Render {
		unique_ptr<Render> Render::mRender = nullptr;

		Render::Render(int iScreenWidth, int iScreenHeight, void* pWindowHandle, RenderType renderType)
		{
			mRenderWidth = iScreenWidth;
			mRenderHeight = iScreenHeight;
			mWindowHandle = pWindowHandle;
			mRenderType = renderType;
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

		RenderType Render::GetRenderType() {
			return mRenderType;
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