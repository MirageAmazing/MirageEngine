#include "Observer.h"

namespace Mirage {
	namespace DesignPattern {
		/****************************The area of Observer*******************************/
		Observer::Observer(Subject* inSubject) {
			subject = inSubject;
		}

		void Observer::TriggerNotification(ObserverMsg* msg) {
			msg->refCount = 0;
			subject->Notify(this, msg);
		}
		void Observer::TriggerNotification(Observer* obj, ObserverMsg* msg) {
			msg->refCount = 0;
			subject->Notify(this, obj, msg);
		}
		void Observer::TriggerNotification(const char* group, ObserverMsg* msg) {
			msg->refCount = 0;
			subject->Notify(this, group, msg);
		}

		void Observer::OnNotify(ObserverMsg* msg) {
			msg->refCount--;
		}

		const char* Observer::GetGroup() {
			return group;
		}

		/****************************The area of Subject*******************************/
		void Subject::Attach(Observer* observer, const char* group) {
			if (group == nullptr)
				return;
			if (strcmp(group, "") == 0)
				return;
			if (observer == nullptr)
				return;

			if (observerGroup.find(group) == observerGroup.end())
				observerGroup[group] = new vector<Observer*>();

			auto findresult = find_if(observerGroup.begin(), observerGroup.end(), [&](pair<const char*, vector<Observer*>*> item) {
				return strcmp(item.first, group) == 0;
			});

			if (findresult != observerGroup.end()) {
				findresult->second->push_back(observer);
			}

			observer->group = (char*)group;
		}
		void Subject::Detach(Observer* observer) {
			if (observer == nullptr)
				return;

			auto heap = observerGroup[observer->GetGroup()];
			auto result = find(heap->begin(), heap->end(), observer);
			if (result != heap->end())
				heap->erase(result);

			if (heap->size() == 0)
				observerGroup.erase(observer->group);
		}

		void Subject::Notify(Observer* source, ObserverMsg* msg) {
			for (auto group : observerGroup) {
				for (auto observer : *group.second) {
					if (observer != source) {
						msg->refCount++;
						ExcuteMsg(observer, msg);
					}
				}
			};
		}
		void Subject::Notify(Observer* source, Observer* target, ObserverMsg* msg) {
			for (auto group : observerGroup) {
				for (auto observer : *group.second) {
					if (observer == target) {
						msg->refCount++;
						ExcuteMsg(observer, msg);
						return;
					}
				}
			}
		}
		void Subject::Notify(Observer* source, const char* groupTarget, ObserverMsg* msg) {
			if (groupTarget == nullptr)
				return;
			for (auto group : observerGroup) {
				if (strcmp(group.first, groupTarget) == 0) {
					for (auto observer : *group.second) {
						if (observer != source) {
							msg->refCount++;
							ExcuteMsg(observer, msg);
						}
					}
					return;
				}
			}
		}
	}
}