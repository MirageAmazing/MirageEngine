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

			MEINLINE shared_ptr<Transform> GetTransform() const{
				return mTransform;
			}
			MEINLINE void SetTransform(shared_ptr<Transform> transform) {
				mTransform = transform;
			}

			MEINLINE void operator = (const Transform& transform) {
				mTransform->SetTranslation(transform.GetTranslation());
				mTransform->SetScale(transform.GetScale());
				mTransform->SetRotate(transform.GetRotate());
			}
			MEINLINE void operator = (const TransformComponent& transform) {
				mTransform->SetTranslation(transform.GetTransform()->GetTranslation());
				mTransform->SetScale(transform.GetTransform()->GetScale());
				mTransform->SetRotate(transform.GetTransform()->GetRotate());
			}

		private:
			shared_ptr<Transform> mTransform;
		};

		using TransformPtr = shared_ptr<Transform>;
	}
}