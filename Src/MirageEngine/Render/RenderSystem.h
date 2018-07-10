#pragma once
/*
The system of render for Mirage.
 */
#include <memory>
#include <list>
#include "../Core/Framework/ISystem.h"
#include "Render/Render.h"
#include "RenderDX11/RenderDX11.h"
#include "RenderOGL4/RenderOGL4.h"
#include "Render/Shader.h"

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
					render = shared_ptr<Render>(new RenderDX11(iScreenWidth, iScreenHeight, pWindowHandle));
					mRender = render;
					break;
#endif
				case RenderType::OpenGL40:
					render = shared_ptr<Render>(new RenderOGL4(iScreenWidth, iScreenHeight, pWindowHandle));
					mRender = render;
					break;
				default:
					break;;
				}
				return render;
			}
			void DestoryRender(RenderPtr render) {
				if (mRender != nullptr)
					mRender.~shared_ptr();
			}

			void Tick() {
				if (mRender != nullptr) {
					mRender->SetClearColor(0, mColor, mColor);
					mRender->Frame();

					if (mColor > 1) mColor = 0;
					else mColor += 0.00001f;
				}
			}
			
			ShaderComplieResult_Ptr ComplieShader(string source, ShaderType type) {
				if (source.length() == 0)
					return nullptr;

				return mRender->LoadOrComplieShader(source, type);
			}

		private:
			float mColor = 0;
			shared_ptr<Render> mRender;

			friend ISystem<RenderSystem>;
		};

	}
}