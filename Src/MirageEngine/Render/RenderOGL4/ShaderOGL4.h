#pragma once
#include "../Render/Shader.h"

namespace Mirage {
	namespace Render {

		using namespace std;

		class ShaderOGL4 :public Shader {
		public:
			ShaderOGL4(string path) :Shader(path) {

			}
		};
	}
}