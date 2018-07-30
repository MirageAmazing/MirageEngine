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
				auto transform = AddComponent<TransformComponent>();
				mTransform = transform->GetTransform();
			}
			ActorEntity(const char* name):Entity(EntityType::Actor) {
				ActorEntity();
			}

			TransformPtr GetTransform() const {
				return mTransform;
			}

		private:
			TransformPtr mTransform;
		};
	}
}