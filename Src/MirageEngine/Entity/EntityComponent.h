#pragma once
#include "..\Core\Core.h"
#include "..\Core\Math\MEMath.h"
#include <memory>
#include <type_traits>
using namespace std;

namespace Mirage {
	namespace Entity {

		class EntityComponent{
		public:
			EntityComponent() {
				mUID = Mirage::Math::GenerateUID();
			}
			EntityComponent(EntityComponent& component) {
				mUID = Mirage::Math::GenerateUID();
			}
			virtual ~EntityComponent() {}

			virtual void Start() {}
			virtual void End() {}
			virtual void Tick() {}
			virtual void Activite(bool value) {}

		private:
			MEUID mUID;
		};

		using EntityComponentPtr = shared_ptr<EntityComponent>;

		#define FromEntityComponentType(T) enable_if<is_base_of<EntityComponent, T>::value, T>::type
	}
}