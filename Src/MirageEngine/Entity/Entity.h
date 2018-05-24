#pragma once
#include <vector>
#include <list>
#include <memory>
#include "Core\Core.h"
#include "Core\Math\MEMath.h"
#include "EntityComponent.h"

using namespace std;

namespace Mirage {
	namespace Entity {

		class Entity;
		using EntityPtr = shared_ptr<Entity>;

		class Entity{
		public:
			Entity() {
				mUID = MirageMath::GenerateUID();
			}
			virtual ~Entity() {
			}
		
		private:
			list<EntityComponentPtr> mEntityList;

			EntityPtr mParent;
			vector<EntityPtr> mChildren;

			MEUID mUID;
		};
	}
}