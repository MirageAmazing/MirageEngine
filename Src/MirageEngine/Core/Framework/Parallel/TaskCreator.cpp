#include "TaskCreator.h"
#include "Scheduler.h"
#include "StateManager.h"

namespace Mirage {
	namespace Framework {
		namespace Parallel {

			ITaskCreator::ITaskCreator() : RigisterToStateMgr {
				Scheduler::Instance()->RegisteTaskCreator(this);
				StateManager::Instance()->Attach(this);
			}

			ITaskCreator::~ITaskCreator() {

			}

			void ITaskCreator::Release() {
				StateManager::Instance()->Detach(this);
				Scheduler::Instance()->UnregisteTaskCreator(this);
			}

			void ITaskCreator::ProduceTask(TaskExecuterType inExecuter, TaskPriority inPriority, TaskLifeCycle inLifecycle) {
				Task task(inExecuter, inPriority, inLifecycle);
				Scheduler::Instance()->PushTask(task, this);
			}

		}
	}
}