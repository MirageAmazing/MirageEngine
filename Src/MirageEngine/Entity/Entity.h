#pragma once
#include <vector>
#include <list>
#include <memory>
#include "..\Core\Core.h"
#include "..\Core\Math\MEMath.h"
#include "..\Core\Math\Transform.h"
#include "EntityComponent.h"

using namespace std;
using namespace Mirage::Math;

namespace Mirage {
	namespace Entity {

		class Entity;
		using EntityPtr = shared_ptr<Entity>;

		class Entity{
		public:
			Entity() {
				mUID = MirageMath::GenerateUID();
			}
			virtual ~Entity() {}
		
			virtual void Start() {}
			virtual void End() {}
			virtual void Tick() {}
			virtual void Activite(bool value) {}

			EntityComponentPtr AddComponent(EntityComponentPtr) {}
			void RemoveComponent(EntityComponentPtr) {}
			
		public:
			Transform mTransform;

		private:
			list<EntityComponentPtr> mEntityList;

			EntityPtr mParent;
			vector<EntityPtr> mChildren;

			MEUID mUID;
		};
	}
}