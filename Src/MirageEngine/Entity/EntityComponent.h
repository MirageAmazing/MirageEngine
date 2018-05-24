#pragma once
#include "..\Core\Core.h"
#include "..\Core\Math\MEMath.h"
#include <memory>
using namespace std;

namespace Mirage {
	namespace Entity {

		class EntityComponent{
		public:
			EntityComponent() {
				mUID = MirageMath::GenerateUID();
			}
			EntityComponent(EntityComponent& component) {
				mUID = MirageMath::GenerateUID();
			}
			virtual ~EntityComponent() {}

			virtual void Start() {}
			virtual void End() {}
			virtual void Tick() {}
			virtual void Activite(bool value) {}

		private:
			MEUID mUID;
		};

		using EntityComponentPtr = unique_ptr<EntityComponent>;
	}
}