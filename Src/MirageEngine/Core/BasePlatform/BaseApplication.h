#pragma once

#include "../Framework/SystemManager.h"
#include "../../Resource/ResourceSystem.h"
#include "../../Entity/EntitySystem.h"
#include "../../Render/RenderSystem.h"
#include "BaseWindow.h"

#include ".././Entity/Component/MeshComponent.h"

namespace Mirage {
	namespace Application {

		using namespace Mirage::Entity;

		/**
		 * /brief Platform application interface
		 */
		class Application
		{
		public:
			Application();
			virtual ~Application();

			virtual void Tick();

			BaseWindow* CreateSingleWindow(WindowDescription WindowDes) const;
			bool DestoryWindow(BaseWindow& window) const;

			bool IsQuit() const;

			void ApplicationStart();

		protected:

			SystemManager* mSysMgr = nullptr;

			bool mIsQuit = false;
		};

	}
}