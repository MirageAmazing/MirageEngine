#pragma once
#include "../../DesignPattern/Singleton.h"

namespace Mirage {
	namespace Framework {
		namespace Parallel {

			using namespace Mirage::DesignPattern;

			class ServiceManager : public Singleton<ServiceManager> {

			};
		}
	}
}