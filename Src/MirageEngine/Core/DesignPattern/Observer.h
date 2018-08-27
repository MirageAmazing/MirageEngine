#pragma once

#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <type_traits>
#include <string>
#include <atomic>
#include <memory.h>

#include "../Core.h"

namespace Mirage {
	namespace DesignPattern {
		using namespace std;

		#define DEFAULT_GROUP "DEFAULT_GROUP_ABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789_~!@#$%^&*()_+"

		class Observer;
		class Subject;

		/// <summary>
		///	The basic message type is used by the observer when communicating with other observers. 
		/// </summary>
		struct ObserverMsg {
		public:
			ObserverMsg() {
				msgName = typeid(*this).name();
				refCount.store(-1);
			}
			ObserverMsg(const ObserverMsg& copy) {
				msgName = copy.msgName;
				targetObserver = copy.targetObserver;
			}
			~ObserverMsg() {}

			MEINLINE string& GetMsgName() {
				return msgName;
			}

			template<class T>
			bool SameType() {
				typename enable_if<is_base_of<ObserverMsg, T>::value, T>::type tempMsg;
				return msgName.compare(tempMsg.GetMsgName().c_str()) == 0;
			}

		private:
			string msgName = "";
			Observer* targetObserver = nullptr;
			atomic<int> refCount;

			friend class Observer;
			friend class Subject;
		};

		/// <summary>
		/// The observer of observer pattern
		/// </summary>
		class Observer {
		public:
			Observer(Subject* inSubject);
			~Observer() {
				for_each(selfCreatedMsgHeap.begin(), selfCreatedMsgHeap.end(), [&](ObserverMsg* item) {
					delete item;
				});
				selfCreatedMsgHeap.clear();
			}

			void TriggerNotification(ObserverMsg* msg);
			void TriggerNotification(Observer* obj, ObserverMsg* msg);
			void TriggerNotification(const char* group, ObserverMsg* msg);

			virtual void OnNotify(ObserverMsg* msg);

			template<class T, class... Args>
			typename enable_if<is_base_of<ObserverMsg, T>::value, T>::type * CreateMsg(Args... args) {

				// Clear all msg that will never be used again(refCount == 0) but it don't contain that not used before(refCount == -1).

				auto heapsize = selfCreatedMsgHeap.size();
				if (heapsize > 0) {
					list<ObserverMsg*> needRemoveHeap;
					for (auto i = selfCreatedMsgHeap.begin(); i != selfCreatedMsgHeap.end(); i++) {
						if ((*i)->refCount == 0) {
							delete (*i);
							needRemoveHeap.push_back(*i);
						}
					}
					for (auto item : needRemoveHeap) {
						selfCreatedMsgHeap.remove(item);
					}
				}

				// Create new msg.

				T* pmsg = new T(forward<Args>(args)...);

				selfCreatedMsgHeap.push_back(pmsg);
				return pmsg;
			}

			const char* GetGroup();

		private:

			list<ObserverMsg*> selfCreatedMsgHeap;
			Subject* subject = nullptr;
			char* group = DEFAULT_GROUP;

			friend class Subject;
		};

		/// <summary>
		/// The subject of observer pattern
		/// </summary>
		class Subject {
		public:
			void Attach(Observer* observer, const char* group = DEFAULT_GROUP);
			void Detach(Observer* observer);

		private:
			void Notify(Observer* source, ObserverMsg* msg);
			void Notify(Observer* source, Observer* target, ObserverMsg* msg);
			void Notify(Observer* source, const char* groupTarget, ObserverMsg* msg);

		protected:
			MEINLINE virtual void ExcuteMsg(Observer* target, ObserverMsg* msg) {
				target->OnNotify(msg);
			}

		protected:
			map<const char*, vector<Observer*>*> observerGroup;

			friend class Observer;
		};
	}
}