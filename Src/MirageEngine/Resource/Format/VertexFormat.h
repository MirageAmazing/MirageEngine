#pragma once
#include "../../Core/Math/Vector3.h"
#include "../../Core/Math/Vector2.h"
#include "../../Core/Math/Color.h"

using namespace MirageMath;

namespace Mirage {
	namespace Resource {
		struct VertexFormat{
			Vector3f position;
			Vector2f uv;
			Colorf color;
		};

		typedef VertexFormat Vertex;
	}
}