#pragma once
#include "../Core/Framework/ISystem.h"
#include "../Core/HAL/MMalloc.h"
#include "./Entity/ActorEntity.h"
#include <list>
#include <algorithm>

namespace Mirage {
	namespace Entity {
		
		class EntitySystem : public System<EntitySystem>{
		public:
			virtual void Initialize() override
			{
				System::Initialize();
			}
			virtual void UnInitialize() override
			{
				System::UnInitialize();
			}
			
			ActorEntity* CreateActorEntity(const char* name) {
				if (name == nullptr)
					return nullptr;
				Core::MMalloc mm;
				auto entity = mm.New<ActorEntity>(name);
				mEntityHeap.push_back(entity);
				return entity;
			}
			void DestoryActorEntity(const char* name) {
				auto r = find(mEntityHeap.begin(), mEntityHeap.end(), [](auto item) {
					return item->Name() == name;
				});
				if (r != mEntityHeap.end())
				{
					Core::MMalloc mm;
					auto entity = (*r);
					mm.Delete<Entity>(entity);
					mEntityHeap.remove(entity);
				}
			}

			virtual void Tick() override {
				for (auto item:mEntityHeap){
					if(item != nullptr)
						item->Tick();
				}
			}

		protected:
			EntitySystem(){
				mVersion = Mirage::Math::VersionNumber(0, 0, 1);
			}
			~EntitySystem(){

			}

		private:
			std::list<EntityPtr> mEntityHeap;

			friend class System<EntitySystem>;
		};

	}
}