#include "BaseApplication.h"

namespace Mirage {
	namespace Application {

		Application::Application() {
			mSysMgr = SystemManager::GetInstance();
			ApplicationStart();
		}
		Application::~Application() {
			mSysMgr->Shutdown();
			mSysMgr = nullptr;
		}

		void Application::Tick() {
			mSysMgr->Tick();
		}

		BaseWindow* Application::CreateSingleWindow(WindowDescription WindowDes) const {
			return nullptr;
		}
		bool Application::DestoryWindow(BaseWindow& window) const {
			return true;
		}

		bool Application::IsQuit() const {
			return mIsQuit;
		}

		void Application::ApplicationStart() {
			auto es = EntitySystem::GetInstance();
			auto actor = es->CreateActorEntity("GameActor");
			auto meshComponent = actor->AddComponent<MeshComponent>();
			auto tranformComponent = actor->GetTransform();

		}

	}
}