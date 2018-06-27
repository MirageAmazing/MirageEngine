#pragma once
#include <string>

namespace Mirage {
	namespace Render {

		using namespace std;

		enum class ShaderType {
			VertexShader,
			HullShader,
			DomainShader,
			GeometryShader,
			PixelShader,
			ComputeShader,
		};

		class Shader {
		public:
			Shader(ShaderType type) {
				mShaderType = type;
			}
			virtual ~Shader() {}

		protected:
			ShaderType mShaderType;
		};
	}
}