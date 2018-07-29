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
				auto transform = make_shared<TransformComponent>();
				AddComponent(transform);
				mTransform = transform->GetTransform();
			}

			TransformPtr GetTransform() const {
				return mTransform;
			}

		private:
			TransformPtr mTransform;
		};
	}
}