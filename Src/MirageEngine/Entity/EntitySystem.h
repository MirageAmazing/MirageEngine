#pragma once
#include "../Core/Framework/ISystem.h"
#include "../Core/HAL/MMalloc.h"
#include "Entity.h"
#include <list>
#include <algorithm>

namespace Mirage {
	namespace Entity {
		
		class EntitySystem :ISystem<EntitySystem>{
		public:
			virtual void Initialize() override
			{
			}
			virtual void UnInitialize() override
			{
			}
			
			EntityPtr CreateEntity(const char* name) {
				if (name == nullptr)
					return nullptr;
				Core::MMalloc mm;
				auto entity = mm.New<Entity>(name);
				mEntityHeap.push_back(entity);
			}
			void DestoryEntity(const char* name) {
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

			void Tick(){
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

			friend ISystem<EntitySystem>;
		};
	}
}