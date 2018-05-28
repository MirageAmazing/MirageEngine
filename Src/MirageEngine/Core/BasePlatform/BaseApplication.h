#pragma once

#include "BaseWindow.h"

namespace Mirage {
	namespace Application {

		/**
		 *Platform application interface
		 */
		class BaseApplication
		{
		public:
			BaseApplication() {}
			virtual ~BaseApplication() {}

			virtual void Tick(float deltaTime) {}

			BaseWindow* CreateWindow(WindowDescription WindowDes) const;
			bool DestoryWindow(BaseWindow& window) const;

		};

	}
}