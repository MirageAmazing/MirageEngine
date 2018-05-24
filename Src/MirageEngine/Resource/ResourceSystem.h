#pragma once
#include <unordered_set>
#include <memory>
#include "../Core/Math/VersionNumber.h"
#include "../Core/Framework/ISystem.h"
#include "Element/IResElement.h"
#include "Element/ResMesh.h"

using namespace std;
using namespace Mirage;

namespace Mirage {
	namespace Resource {
		class ResouceSystem final :public ISystem<ResouceSystem>{
		public:
			virtual void Initialize() override
			{
			}
			virtual void UnInitialize() override
			{
			}

			shared_ptr<ResMesh> CreateMeshRes()
			{
				shared_ptr<ResMesh> mesh(new ResMesh());
				shared_ptr<IResElement> resElement = dynamic_pointer_cast<IResElement>(mesh);
				mResElementHeap.insert(resElement);
				return mesh;
			};
			bool DeleteMeshRes(shared_ptr<ResMesh> resMesh)
			{
				shared_ptr<IResElement> resElement = dynamic_pointer_cast<IResElement>(resMesh);
				if (mResElementHeap.find(resElement) != mResElementHeap.end())
				{
					mResElementHeap.erase(resElement);
					return true;
				}
				else
					return false;
			}

		protected:
			ResouceSystem()
			{
				mVersion = VersionNumber(0, 0, 1);
			}
			~ResouceSystem()
			{

			}

		private:
			unordered_set<shared_ptr<IResElement>> mResElementHeap;

			friend ISystem<ResouceSystem>;
		};
	}
}