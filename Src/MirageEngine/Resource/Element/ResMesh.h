#pragma once
#include <list>
#include <vector>
#include "IResElement.h"
#include "../Format/VertexFormat.h"

using namespace std;

namespace Mirage {
	namespace Resource {

		class ResMesh :public IResElement
		{
		public:
			ResMesh(){
				mElementType = eResElementType::Mesh;
			}
			~ResMesh() {
			}

		public:
			void SetVertexs(list<VertexFormat> vertexs) {
				mVertexList = vertexs;
			}
			void AddVertex(Vertex vertex) {
				mVertexList.push_back(vertex);
			}
			list<VertexFormat> GetVertexs() {
				return mVertexList;
			}
			void SetIndices(list<uint32> indices) {
				mIndices = indices;
			}
			list<uint32> GetIndices() {
				return mIndices;
			}
			void Clear() {
				mVertexList.clear();
			}

		private:
			list<VertexFormat> mVertexList;
			list<uint32> mIndices;
		};

		using ResMeshPtr = std::shared_ptr<ResMesh>;
	}
}