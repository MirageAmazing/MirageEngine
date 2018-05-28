#pragma once
/*
The system of render for Mirage.
 */
#include <memory>
#include <list>
#include "../Core/Framework/ISystem.h"
#include "../Core/Math/VersionNumber.h"
#include "BaseRender\BaseRender.h"
#include "RenderDX11\RenderDX11.h"
#include "RenderOGL4\RenderOGL4.h"

using namespace std;

namespace Mirage {
	namespace Render {
		
		class RenderSystem :ISystem<RenderSystem> {
		public:
			virtual void Initialize() override
			{
			}
			virtual void UnInitialize() override
			{
			}
			
			shared_ptr<Render> CreateRender(RenderType type, int iScreenWidth, int iScreenHeight, void* pWindowHandle) {
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
					if (mBaseRender == nullptr)
						mBaseRender = unique_ptr<BaseRender>(new RenderOGL4(iScreenWidth, iScreenHeight, pWindowHandle));
					return move(mBaseRender);
				#endif
				}

				return nullptr;
			}

		private:
			list<shared_ptr<Render>> mRenderHeap;

			friend ISystem<RenderSystem>;
		};

	}
}