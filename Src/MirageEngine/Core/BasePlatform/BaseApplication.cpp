#include "BaseApplication.h"
#include "../Framework/Parallel/ParallelFramework.h"

namespace Mirage {
	namespace Application {

		using namespace Mirage::Framework::Parallel;

		Application::Application() {
			ParallelFramework::Instance()->Initialize();
			mSysMgr = SystemManager::GetInstance();
			ApplicationStart();
		}
		Application::~Application() {
			mSysMgr->Shutdown();
			mSysMgr = nullptr;
			ParallelFramework::Instance()->UnInitialize();
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