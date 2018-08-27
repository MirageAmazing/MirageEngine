#pragma once
#include "../../DesignPattern/Observer.h"
#include "Task.h"

namespace Mirage {
	namespace Framework {
		namespace Parallel {

			using namespace Mirage::DesignPattern;

			/// <summary>
			/// The creator of task.
			/// </summary>
			class ITaskCreator : public Observer {
			public:
				ITaskCreator();
				~ITaskCreator();
				void Release();
				void ProduceTask(TaskExecuterType inExecuter, TaskPriority inPriority, TaskLifeCycle inLifecycle);
			};

			using ITaskCreator_ptr = ITaskCreator*;
		}
	}
}