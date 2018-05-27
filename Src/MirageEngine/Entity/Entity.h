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

		class EntitySystem;
		class Entity;
		using EntityPtr = Entity*;

		class Entity{
		protected:
			Entity(const char* name) {
				mUID = MirageMath::GenerateUID();
				mName = name;
			}
			virtual ~Entity() {}
		
			virtual void Start() {}
			virtual void End() {}
			virtual void Tick() {}
			virtual void Activite(bool value) {}

		public:
			const char* Name() {
				return mName;
			}
			EntityComponentPtr AddComponent(EntityComponentPtr) {

			}
			void RemoveComponent(EntityComponentPtr) {

			}
			
		public:
			Transform mTransform;

		private:
			const char* mName;

			list<EntityComponentPtr> mEntityList;

			EntityPtr mParent;
			vector<EntityPtr> mChildren;

			MEUID mUID;

			friend EntitySystem;
		};
	}
}