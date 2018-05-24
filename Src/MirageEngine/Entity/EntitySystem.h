#pragma once
#include "../Framework/ISystem.h"
#include "../Math/VersionNumber.h"

namespace Mirage {
	namespace Entity {
		
		class EntitySystem :ISystem<EntitySystem>{
		public:
			virtual void Initialize() override
			{
			}
			virtual void UnInitialize() override
			{
			}

		protected:
			EntitySystem()
			{
				mVersion = MirageMath::VersionNumber(0, 0, 1);
			}
			~EntitySystem()
			{

			}

			friend ISystem<EntitySystem>;
		};
	}
}