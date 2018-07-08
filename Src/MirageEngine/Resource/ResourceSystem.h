#pragma once
#include <unordered_set>
#include <string>
#include <memory>
#include "../Core/Framework/ISystem.h"
#include "../Render/RenderSystem.h"
#include "Element/IResElement.h"
#include "Element/ResMesh.h"
#include "Element/ResShader.h"

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
			shared_ptr<ResMesh> CreateMeshRes(list<VertexFormat>& vertexs, list<uint32>& indices)
			{
				shared_ptr<ResMesh> mesh(new ResMesh(vertexs, indices));
				shared_ptr<IResElement> resElement = dynamic_pointer_cast<IResElement>(mesh);
				mResElementHeap.insert(resElement);
				return mesh;
			};
			shared_ptr<ResShader> CreateShaderRes(string source, ShaderType shaderType) {
				shared_ptr<ResShader> shader(new ResShader(source, shaderType));
				shared_ptr<IResElement> resElement = dynamic_pointer_cast<IResElement>(shader);
				mResElementHeap.insert(resElement);
				return shader;
			}
			bool DeleteMeshRes(shared_ptr<ResMesh> resMesh) {
				DeleteRes(dynamic_pointer_cast<IResElement>(resMesh));
			}
			bool DeleteShaderRes(shared_ptr<ResShader> resShader) {
				return DeleteRes(dynamic_pointer_cast<IResElement>(resShader));
			}
		public:
			ResouceSystem()
			{
				mVersion = VersionNumber(0, 0, 1);
			}
			~ResouceSystem()
			{

			}

		private:
			bool DeleteRes(shared_ptr<IResElement> res) {
				if (mResElementHeap.find(res) != mResElementHeap.end())
				{
					mResElementHeap.erase(res);
					return true;
				}
				else
					return false;
			}

		private:
			unordered_set<shared_ptr<IResElement>> mResElementHeap;

			friend ISystem<ResouceSystem>;
		};

	}
}