#pragma once
#include <map>
#include <queue>
#include <functional>
#include "../../DesignPattern/Singleton.h"
#include "../../DesignPattern/Observer.h"
#include "TaskManager.h"
#include "Scheduler.h"

namespace Mirage {
	namespace Framework {
		namespace Parallel {

			/// <summary>
			/// Manage the state of task and universal scene and object. Manage the communication of task and universal scene and object
			/// </summary>
			class StateManager : public Singleton<StateManager>, public Subject {
			public:
				virtual void Initialize() override {
				}
				virtual void UnInitialize() override {
				}

			private:
				MEINLINE virtual void ExcuteMsg(Observer* target, ObserverMsg* msg) override {
					if (target == nullptr)
						return;
					Task task([=]() { target->OnNotify(msg); }, TaskPriority::High, TaskLifeCycle::Once);
					Scheduler::Instance()->PushTask(task, (ITaskCreator*)target);
				}

			private:
			};

			#define RigisterToStateMgr Observer(StateManager::Instance())
		}
	}
}