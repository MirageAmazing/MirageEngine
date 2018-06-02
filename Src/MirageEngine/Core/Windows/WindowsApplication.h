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
				mWindowPtr = WindowsWindow::Make(this, "Mirage", 80, 80, 800, 600);
				auto size = mWindowPtr->Size();
				mRenderSystem = RenderSystem::GetInstance();
				mRenderSystem->CreateRender(RenderType::DirectX11, size.x, size.y, mWindowPtr->GetHWND());			
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