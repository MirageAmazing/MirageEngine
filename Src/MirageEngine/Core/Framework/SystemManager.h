#pragma once
#include <map>
#include <string>
#include <memory>
#include <type_traits>
#include "ISystem.h"
#include "../HAL/MMalloc.h"

namespace Mirage {

	using namespace std;

	class SystemManager {
	public:
		static SystemManager* GetInstance();
		static void Shutdown();

		template<class T>
		bool RegisterSystem(shared_ptr<FromISystemType(T)> system) {
			if (system == nullptr) return false;
			string name = system->GetSystemName();
			//if (mSystemMap.find(name) == mSystemMap.end() && mSystemMap.size() > 0) return false;

			shared_ptr<ISystem> systemInterface = static_pointer_cast<ISystem>(system);
			mSystemMap[name] = systemInterface;
			return true;
		}
		template<class T>
		bool UnregisterSystem(shared_ptr<FromISystemType(T)> system)
		{
			if (system == nullptr) return false;
			string name = system->GetSystemName();
			if (mSystemMap.find(name) == mSystemMap.end()) return false;

			auto system = mSystemMap[name];
			if (system == nullptr) return false;

			system->UnInitialize();
			mSystemMap.erase(name);

			return true;
		}
		void Tick();

	private:
		SystemManager() {}
		~SystemManager() {}

		map<string, shared_ptr<ISystem>> mSystemMap;

		static SystemManager* mInstance;
		friend class Core::MMalloc;
	};

}