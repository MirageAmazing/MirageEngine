#pragma once
#include <vector>
#include <memory>
#include <algorithm>
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

		enum class EntityType {
			Actor,

			Error
		};

		class Entity{
		protected:
			Entity(EntityType type) {
				mType = type;
			}
			Entity(const char* name) {
				mUID = Mirage::Math::GenerateUID();
				mName = name;
			}
			virtual ~Entity() {
				
			}
		
			virtual void Start() {}
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
			virtual void Activite(bool value) {}
					

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
			EntityComponentPtr AddComponent(EntityComponentPtr component) {
				if (component != nullptr)
				{
					component->Start();
					mEntityComList.push_back(component);
				}
			}
			void RemoveComponent(EntityComponentPtr component) {
				auto pos = find(mEntityComList.begin(), mEntityComList.end(), component);
				if (pos == mEntityComList.end())
					component->End();
				mEntityComList.erase(pos);
			}
			
		public:
			Transform mTransform;

		private:
			EntityType mType;
			const char* mName;

			vector<EntityComponentPtr> mEntityComList;

			EntityPtr mParent;
			vector<EntityPtr> mChildren;

			MEUID mUID;

			friend EntitySystem;
		};
	}
}