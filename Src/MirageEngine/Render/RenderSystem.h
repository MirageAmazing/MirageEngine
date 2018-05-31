#pragma once
/*
The system of render for Mirage.
 */
#include <memory>
#include <list>
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
				switch (type)
				{
#if defined(MIRAGE_PLATFORM_WINDOWS)
				case RenderType::DirectX11:
					auto render = shared_ptr<Render>(new RenderDX11(iScreenWidth, iScreenHeight, pWindowHandle));
					mRenderHeap.push_back(render);
					return render;
#endif
#if defined(MIRAGE_PLATFORM_LINUX)
				case RenderType::OpenGL40:
					auto render = shared_ptr<Render>(new RenderOGL4(iScreenWidth, iScreenHeight, pWindowHandle));
					mRenderHeap.push_back(render);
					return render;
#endif
				}

				return nullptr;
			}
			void DestoryRender(RenderPtr render) {
				mRenderHeap.remove(render);
			}

			void Tick() {
				for (auto render : mRenderHeap) {
					render->SetClearColor(0, mColor, mColor);
					render->Frame();

					if (mColor > 1) mColor = 0;
					else mColor += 0.001f;
					render->Frame();
				}
			}
			
		private:
			float mColor = 0;
			list<shared_ptr<Render>> mRenderHeap;

			friend ISystem<RenderSystem>;
		};

	}
}