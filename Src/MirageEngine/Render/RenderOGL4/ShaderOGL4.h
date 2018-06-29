#pragma once
#include <memory>
#include <GL\glew.h>
#include "../Render/Shader.h"
#include "../RenderOGL4/RenderOGL4.h"

namespace Mirage {
	namespace Render {

		using namespace std;

		class VertexShaderOGL4 :public VertexShader {
		public:
			VertexShaderOGL4(string codeSource) :VertexShader() {

			}
		};
	}
}