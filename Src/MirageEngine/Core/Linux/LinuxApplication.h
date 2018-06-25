#pragma once
#include "MirageEngine.h"
#if defined(MIRAGE_PLATFORM_LINUX)

#include <memory>
#include "../BasePlatform/BaseApplication.h"
#include "LinuxWindow.h"
#include "../../Render/RenderSystem.h"

namespace Mirage {
	namespace Application {

		using namespace Mirage::Render;

		/**
		 *Linux application
		 */
		class LinuxApplication :public Application
		{
		public:
			static LinuxApplication* CreateApplication() {
				return nullptr;
			}

		public:
			LinuxApplication(){						
				mWindow = LinuxWindow::Make(this, "Mirage", 80, 80, 800, 600);
				auto size = mWindow->Size();
				mRenderSystem = RenderSystem::GetInstance();
				mRenderSystem->CreateRender(RenderType::OpenGL40, size.x, size.y, mWindow->GetWindowHandle());
			}
			~LinuxApplication() {
				mWindow.release();
			}

			virtual void Tick() override {
				mWindow->Tick();
				mRenderSystem->Tick();

				mIsQuit = mWindow->IsQuit();
			}

		private:

			std::shared_ptr<RenderSystem> mRenderSystem;
			std::unique_ptr<LinuxWindow> mWindow;
		};
	}
}

#endif