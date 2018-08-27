#pragma once
#include "../DesignPattern/Singleton.h"

namespace Mirage {
	namespace Application {

		using namespace Mirage::DesignPattern;

		/// <summary>
		///  Make function what depend on platform be transparency for upper-level system.
		/// </summary>
		class Platform {
		public:
			Platform() {}
			~Platform() {}
		};
	}
}