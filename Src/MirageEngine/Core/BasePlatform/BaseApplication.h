#pragma once

#include "BaseWindow.h"

namespace Mirage {
	namespace Application {

		/**
		 *Platform application interface
		 */
		class Application
		{
		public:
			Application() {}
			virtual ~Application() {}

			virtual void Tick() {}

			BaseWindow* CreateSingleWindow(WindowDescription WindowDes) const {
				return nullptr;
			}
			bool DestoryWindow(BaseWindow& window) const {
				return true;
			}

			bool IsQuit() const {
				return mIsQuit;
			}

		protected:

			bool mIsQuit = false;
		};

	}
}