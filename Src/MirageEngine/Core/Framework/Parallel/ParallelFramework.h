#pragma once
#include "../../DesignPattern/Singleton.h"
#include "StateManager.h"
#include "TaskManager.h"
#include "Scheduler.h"

namespace Mirage {
	namespace Framework {
		namespace Parallel {

			using namespace Mirage::DesignPattern;

			class ParallelFramework : public Singleton<ParallelFramework> {
			public:
				virtual void Initialize() override {
					TaskManager::Instance()->Initialize();
					StateManager::Instance()->Initialize();
					Scheduler::Instance()->Initialize();
				}
				virtual void UnInitialize() override {
					Scheduler::Instance()->UnInitialize();
					StateManager::Instance()->UnInitialize();
					TaskManager::Instance()->UnInitialize();
				}

			};
		}
	}
}