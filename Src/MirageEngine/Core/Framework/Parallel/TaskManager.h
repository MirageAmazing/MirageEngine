#pragma once
#include <list>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <memory>
#include <future>
#include <thread>
#include <mutex>
#include <atomic>
#include "Task.h"
#include "TaskCreator.h"
#include "../../DesignPattern/Singleton.h"
#include "../../Misc/Timer.h"

namespace Mirage {
	namespace Framework {
		namespace Parallel {

			using namespace std;
			using namespace Mirage::DesignPattern;
			using namespace Mirage::Misc;

			/// <summary>
			/// The manager of task
			/// </summary>
			class TaskManager : public Singleton<TaskManager> {
			public:

				/// <summary>
				/// The state of task pipline.
				/// </summary>
				enum class TaskPipelineState {
					Busyness,
					Idle,

					Error
				};

				/// <summary>
				/// The pipline of task.
				/// </summary>
				class TaskPipline {
				public:
					TaskPipline(uint32 workId) {
						id = workId;
						state.store(TaskPipelineState::Idle);
					}
					~TaskPipline() {}

					uint32 GetID() {
						return id;
					}

					void PushTask(const Task& task) {
						lock_guard<mutex> lock(piplinemutex);
						taskHeap.push_back(task);
					}

					uint32 GetTaskCount() {
						lock_guard<mutex> lock(piplinemutex);
						return taskHeap.size();
					}
					TaskPipelineState GetState() {
						lock_guard<mutex> lock(piplinemutex);
						return state;
					}
					float GetIdleTime() {
						lock_guard<mutex> lock(piplinemutex);
						return timer.GetIdleTime();
					}
					float GetAvergerFramerate() {
						lock_guard<mutex> lock(piplinemutex);
						return timer.GetAvergerFramerate();
					}
					void Work() {					
						while (!isShutdown)
						{
							{
								lock_guard<mutex> lock(piplinemutex);
								timer.Tick();
								if (taskHeap.size() > 0) {
									timer.Start();
									state = TaskPipelineState::Busyness;

									for (auto nrtIt = needRemoveTask.begin(); nrtIt != needRemoveTask.end(); nrtIt++) {
										taskHeap.erase(*nrtIt);
									}
									needRemoveTask.clear();

									for (auto it = taskHeap.begin(); it != taskHeap.end(); it++) {
										it->Execute();
										if (it->CouldBeDestory())
											needRemoveTask.push_back(it);
									}
								}
								else {
									timer.Pause();
									state = TaskPipelineState::Idle;
									this_thread::sleep_for(chrono::microseconds(100));
								}
							}
						}
					}

				private:

					list<Task> taskHeap;
					list<list<Task>::iterator> needRemoveTask;
					atomic<TaskPipelineState> state;
					uint32 id = 0;
					Timer timer;
					mutex piplinemutex;
				};

				using Pipline_ptr = shared_ptr<TaskManager::TaskPipline>;

			public:

				virtual void Initialize() override {
					Singleton::Initialize();

					isShutdown.store(false);
					threadNum = thread::hardware_concurrency();

					for (int i = 0; i < threadNum; i++) {
						Pipline_ptr wl = make_shared<TaskManager::TaskPipline>(i + 1);
						uint32 id = wl->GetID();
						pipelines[id] = wl;
						piplineIDs.push_back(id);

						thread* threadwork = new thread([=]() { wl->Work(); });
						threadPool.push_back(threadwork);
					}
				}
				virtual void UnInitialize() override {
					Singleton::UnInitialize();
					isShutdown = IsUnInitialize();

					for (auto item : threadPool) {
						if (item != nullptr) {
							item->join();
							delete item;
						}
					}

					threadPool.clear();
					pipelines.clear();
				}

				void Tick() {
					/*if(mainthreadWorkLine != nullptr)
						mainthreadWorkLine->Work();*/
				}

				void PushTask(Task& task, short pipeline) {
					pipelines[pipeline]->PushTask(task);
				}

				list<uint32> GetAllTaskLineID() {
					return piplineIDs;
				}

				TaskPipelineState GetPipelineState(uint32 id) {
					return pipelines[id]->GetState();
				}
				uint32 GetTaskLineCount(uint32 id) {
					return pipelines[id]->GetTaskCount();
				}
				uint32 GetMaxPerformancePipeline() {
					uint32 pipeline = pipelines.begin()->first;
					float fps = pipelines.begin()->second->GetAvergerFramerate();
					float temp = 0;

					for (auto item : pipelines) {
						temp = item.second->GetAvergerFramerate();
						if (fps <= temp) {
							pipeline = item.first;
							fps = temp;
						}
					}

					return pipeline;
				}
				uint32 GetTheMostFreePipeline() {
					uint32 pipeline = pipelines.begin()->first;
					float time = pipelines.begin()->second->GetIdleTime();
					float temp = 0;

					for (auto item : pipelines) {
						temp = item.second->GetIdleTime();
						if (time <= temp) {
							pipeline = item.first;
							time = temp;
						}
					}

					return pipeline;
				}
				uint32 GetMinumumPipeline() {
					uint32 pipeline = pipelines.begin()->first;
					uint32 taskCount = pipelines.begin()->second->GetTaskCount();
					uint32 temp = 0;

					for (auto item : pipelines) {
						temp = item.second->GetTaskCount();
						if (taskCount > temp) {
							pipeline = item.first;
							taskCount = temp;
						}
					}

					return pipeline;
				}
			private:

				map<uint32, Pipline_ptr> pipelines;
				list<uint32> piplineIDs;
				vector<thread*> threadPool;

				uint32 threadNum = 0;
				static atomic_bool isShutdown;
			};
		}
	}
}