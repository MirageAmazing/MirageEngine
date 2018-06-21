#pragma once
#include "../EntityComponent.h"
#include "../../Resource/Element/ResMesh.h"

using namespace Mirage::Resource;

namespace Mirage {
	namespace Entity {
		class MeshComponent :public EntityComponent {
		public:
			MeshComponent() {}
			~MeshComponent() {}

			void SetMesh(ResMeshPtr mesh) {
				mMesh = mesh;
			}
			ResMeshPtr GetMesh() {
				return mMesh;
			}

		private:
			ResMeshPtr mMesh;
		};
	}
}