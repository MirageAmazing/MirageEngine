#pragma once
#include "../Framework/ISystem.h"

namespace Mirage {

	class MObjectSystem : System<MObjectSystem>{
	public:
		virtual void Initialize() override
		{
			System::Initialize();
		}
		virtual void UnInitialize() override
		{
			System::UnInitialize();
		}

		friend class System<MObjectSystem>;
	};

}