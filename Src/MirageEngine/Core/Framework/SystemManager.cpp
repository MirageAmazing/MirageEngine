#include "SystemManager.h"
#include "../MObject/MObjectSystem.h"
#include "../../Entity/EntitySystem.h"
#include "../../Resource/ResourceSystem.h"
#include "../../Render/RenderSystem.h"

namespace Mirage {
	
	SystemManager* SystemManager::mInstance = nullptr;

	SystemManager* SystemManager::GetInstance() {
		if (mInstance == nullptr)
		{
			mInstance = Core::mmalloc.New<SystemManager>();

			mInstance->RegisterSystem<Resource::ResouceSystem>(Resource::ResouceSystem::GetInstance());
			mInstance->RegisterSystem<Entity::EntitySystem>(Entity::EntitySystem::GetInstance());
			mInstance->RegisterSystem<Render::RenderSystem>(Render::RenderSystem::GetInstance());
		}
		return mInstance;
	}

	void SystemManager::Shutdown() {
		if (mInstance != nullptr)
		{
			for (auto item : mInstance->mSystemMap) {
				item.second->UnInitialize();
			}
			Core::mmalloc.Delete<SystemManager>(mInstance);
		}
		mInstance = nullptr;
	}

	void SystemManager::Tick() {
		for (auto item : mSystemMap) {
			item.second->Tick();
		}
	}

}