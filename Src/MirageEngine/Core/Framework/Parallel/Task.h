#pragma once
#include "../../Core.h"
#include <functional>
using namespace std;

namespace Mirage {
	namespace Framework {
		namespace Parallel {
			/// <summary>
			/// Priority of task
			/// </summary>
			enum class TaskPriority : short {
				High = 2,
				Middle = 1,
				Low = 0
			};

			/// <summary>
			/// This property determines that how many times task will be executed by TaskPipline
			/// </summary>
			enum class TaskLifeCycle {
				Once,
				Forever,
			};

			using TaskExecuterType = function<void(void)>;

			/// <summary>
			/// Task
			/// </summary>
			class Task {
			public:
				Task(const TaskExecuterType& inExecuter, const TaskPriority inPriority, const TaskLifeCycle inLifecycle) {
					priority = (short)inPriority;
					lifecycle = inLifecycle;
					executer = inExecuter;

					switch (lifecycle)
					{
					case TaskLifeCycle::Forever:
						lifetime = -1;
						break;
					case TaskLifeCycle::Once:
						lifetime = 1;
						break;
					default:
						break;
					}
				}
				Task(const Task& task) {
					priority = task.priority;
					lifecycle = task.lifecycle;
					executer = task.executer;
					lifetime = task.lifetime;
				}

				MEINLINE short Priority() const {
					return priority;
				}
				MEINLINE void Execute() {
					if (lifetime == 0)
						return;
					executer();
					if (lifecycle != TaskLifeCycle::Forever)
						lifetime--;
				}
				MEINLINE bool CouldBeDestory() const {
					return lifetime == 0;
				}

			private:

				short priority = (int)TaskPriority::Low;
				TaskLifeCycle lifecycle = TaskLifeCycle::Once;
				TaskExecuterType executer;
				int lifetime = 1;
			};
		}
	}
}