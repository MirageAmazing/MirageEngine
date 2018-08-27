#pragma once
#include <map>
#include "../../DesignPattern/Singleton.h"
#include "TaskManager.h"

using namespace std;

namespace Mirage {
	namespace Framework {
		namespace Parallel {

			/// <summary>
			/// Be responsible for scheduling all parallel tasks. 
			/// </summary>
			class Scheduler : public Singleton<Scheduler> {
			public:
				virtual void Initialize() override {
					taskMgr = TaskManager::Instance();
				}
				virtual void UnInitialize() override {
				}

				void RegisteTaskCreator(ITaskCreator_ptr taskCreator) {
					auto taskLineIDList = taskMgr->GetAllTaskLineID();
					for (auto item : taskCreatorHeap) {
						taskLineIDList.remove(item.second);
					}

					// If have free line, attach this taskcreator to it
					if (taskLineIDList.size() > 0)
					{
						taskCreatorHeap[taskCreator] = *taskLineIDList.begin();
						return;
					}

					// Or haven't, attach this taskcreator to a line that have least taskcreator.
					taskCreatorHeap[taskCreator] = taskMgr->GetTheMostFreePipeline();
				}
				void UnregisteTaskCreator(ITaskCreator_ptr taskCreator) {
					auto result = find_if(taskCreatorHeap.begin(), taskCreatorHeap.end(), [taskCreator](const pair<ITaskCreator_ptr, uint32>& a)->bool {
						return a.first == taskCreator;
					});
					if (result != taskCreatorHeap.end()) {
						taskCreatorHeap.erase(result);
					}
				}

				void PushTask(Task& task, ITaskCreator_ptr taskCreator) {
					taskMgr->PushTask(task, taskCreatorHeap[taskCreator]);
				}
				void PushTask(Task& task) {
					taskMgr->PushTask(task, taskMgr->GetMinumumPipeline());
				}

			private:

				map<ITaskCreator_ptr, uint32> taskCreatorHeap;
				TaskManager* taskMgr;
			};
		}
	}
}