#pragma once
#include <memory>
#include "../Entity.h"
#include "../Component/TransformComponent.h"

namespace Mirage {
	namespace Entity {

		using namespace std;

		class ActorEntity : public Entity{
		public:
			ActorEntity() :Entity(EntityType::Actor) {
				AddComponent(make_shared<TransformComponent>());
			}
		};

	}
}