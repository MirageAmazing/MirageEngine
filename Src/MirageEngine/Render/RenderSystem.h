#pragma once
/*
The system of render for Mirage.
 */
#include <memory>
#include <list>
#include "SDL2/SDL_syswm.h"
#include "../Core/Framework/ISystem.h"
#include "BaseRender/BaseRender.h"
#include "RenderDX11/RenderDX11.h"
#include "RenderOGL4/RenderOGL4.h"

using namespace std;

namespace Mirage {
	namespace Render {
		
		class RenderSystem : public ISystem<RenderSystem> {
		public:
			virtual void Initialize() override
			{
			}
			virtual void UnInitialize() override
			{
			}
			RenderPtr CreateRender(RenderType type, int iScreenWidth, int iScreenHeight, void* pWindowHandle) {
				RenderPtr render = nullptr;
				switch (type)
				{
#if defined(MIRAGE_PLATFORM_WINDOWS)
				case RenderType::DirectX11:
					SDL_SysWMinfo wmInfo;
					SDL_VERSION(&wmInfo.version);
					SDL_GetWindowWMInfo((SDL_Window*)pWindowHandle, &wmInfo);
					render = shared_ptr<Render>(new RenderDX11(iScreenWidth, iScreenHeight, wmInfo.info.win.window));
					mRenderHeap.push_back(render);
					break;
#endif
				case RenderType::OpenGL40:
					render = shared_ptr<Render>(new RenderOGL4(iScreenWidth, iScreenHeight, pWindowHandle));
					mRenderHeap.push_back(render);
					break;
				default:
					break;;
				}
				return render;
			}
			void DestoryRender(RenderPtr render) {
				mRenderHeap.remove(render);
			}

			void Tick() {
				for (auto render : mRenderHeap) {
					render->SetClearColor(0, mColor, mColor);
					render->Frame();

					if (mColor > 1) mColor = 0;
					else mColor += 0.00001f;
				}
			}
			
		private:
			float mColor = 0;
			list<shared_ptr<Render>> mRenderHeap;

			friend ISystem<RenderSystem>;
		};

	}
}