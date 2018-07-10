#pragma once

#include <memory>
#include "../EntityComponent.h"
#include "../Core/Math/Transform.h"

namespace Mirage {
	namespace Entity {

		using namespace std;
		using namespace Mirage::Math;

		class TransformComponent :public EntityComponent {
		public:
			TransformComponent() {
				mTransform = make_shared<Transform>();
			}
			~TransformComponent() {
			
			}

			shared_ptr<Transform> GetTransform() {
				return mTransform;
			}
			void SetTransform(shared_ptr<Transform> transform) {
				mTransform = transform;
			}

		private:
			shared_ptr<Transform> mTransform;
		};
	}
}