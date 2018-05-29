#pragma once

#include "../BasePlatform/BaseApplication.h"

namespace Mirage {
	namespace Application {
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
			~LinuxApplication() {
			}

			virtual void Tick() override {

			}
		private:
			LinuxApplication();
		};
	}
}