#pragma once
#include "MirageEngine.h"
#if defined(MIRAGE_PLATFORM_WINDOWS)

#include "../BasePlatform/BaseApplication.h"
#include "../Windows/WindowsWindow.h"
#include "../../Render/RenderSystem.h"
#include "../Math/Vector3.h"
#include "../Math/Camera.h"

namespace Mirage{
	namespace Application {

		using namespace Mirage::Math;
		using namespace Mirage::Render;

		/**
		*Windows application
		*/
		class WindowsApplication :public Application
		{
		public:
			WindowsApplication() {
				RenderType renderType = RenderType::DirectX11;

				mWindowPtr = WindowsWindow::Make(this, "Mirage", 80, 80, 800, 600, renderType);
				auto size = mWindowPtr->Size();
				mRenderSystem = RenderSystem::GetInstance();
				mRenderSystem->CreateRender(renderType, size.x, size.y, 
					renderType == RenderType::DirectX11 ? (void*)(mWindowPtr->GetHWND()) : mWindowPtr->GetWindowHandle());
			}
			~WindowsApplication() {
				mWindowPtr.release();
			}
			virtual void Tick() override {
				mWindowPtr->Tick();
				mRenderSystem->Tick();

				mIsQuit = mWindowPtr->IsQuit();
			}

		private:
			shared_ptr<RenderSystem> mRenderSystem;
			unique_ptr<WindowsWindow> mWindowPtr;
		};
	}
}

#endif