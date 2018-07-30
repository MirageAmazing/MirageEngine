#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "..\Core\Core.h"
#include "..\Core\HAL\MMalloc.h"
#include "..\Core\MObject\MObject.h"
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

		enum class EntityType {
			Actor,

			Error
		};

		class Entity : public MObject{
		public:
			Entity(EntityType type) {
				mType = type;
			}
			Entity(const char* name) {
				mUID = Mirage::Math::GenerateUID();
				mName = name;
			}
			virtual ~Entity() {
				
			}
		
			virtual void Start() {
			}
			virtual void End() {
				for (auto item : mEntityComList) {
					item->End();
				}
			}
			virtual void Tick() {
				for (auto item : mEntityComList) {
					item->Tick();
				}
				for (auto child : mChildren) {
					child->Tick();
				}
			}
			virtual void Activite(bool value) {
				mActivite = value;
			}
			
			MEINLINE bool IsActivite() {
				return mActivite;
			}

		public:
			const char* GetName() {
				return mName;
			}
			EntityType GetType() {
				return mType;
			}
			void SetName(const char* name) {
				mName = name;
			}

			template<class T>
			shared_ptr<T> AddComponent() {
				auto component = Core::mmalloc.MakeShared<T>();
				if (component != nullptr)
				{
					component->Start();
					auto baseComponent = dynamic_pointer_cast<EntityComponent, T>(component);
					mEntityComList.push_back(baseComponent);
				}
				return component;
			}

			template<class T>
			void RemoveComponent(shared_ptr<FromEntityComponentType(T)> component) {
				auto baseComponent = dynamic_pointer_cast<EntityComponent, T>(component);
				auto pos = find(mEntityComList.begin(), mEntityComList.end(), baseComponent);
				if (pos == mEntityComList.end())
					baseComponent->End();
				mEntityComList.erase(pos);
			}
			
		public:
			Transform mTransform;

		private:
			EntityType mType;
			const char* mName;

			bool mActivite = true;

			vector<EntityComponentPtr> mEntityComList;

			EntityPtr mParent;
			vector<EntityPtr> mChildren;

			MEUID mUID;

			friend EntitySystem;
		};
	}
}