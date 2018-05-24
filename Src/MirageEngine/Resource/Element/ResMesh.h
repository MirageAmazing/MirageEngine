#pragma once
#include <list>
#include "IResElement.h"
#include "../Format/VertexFormat.h"

using namespace std;

namespace Mirage {
	namespace Resource {
		class ResMesh :IResElement
		{
		public:
			ResMesh()
			{
				mElementType = eResElementType::Mesh;
			}
			~ResMesh() {}

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
			void Clear() {
				mVertexList.clear();
			}

		private:
			list<VertexFormat> mVertexList;
			list<uint32> mIndices;
		};
	}
}