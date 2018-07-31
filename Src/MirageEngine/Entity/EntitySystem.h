#pragma once
#include "../Core/Framework/ISystem.h"
#include "../Core/HAL/MMalloc.h"
#include "./Entity/ActorEntity.h"
#include <string.h>
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
				for (auto item : mEntityHeap){
					if (strcmp(item->GetName(), name) == 0) {
						Core::mmalloc.Delete<Entity>(item);
						mEntityHeap.remove(item);
					}
				}
			}

			virtual void Tick() override {
				for (auto item:mEntityHeap){
					if(item != nullptr)
						item->Tick();
				}
			}

		public:
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