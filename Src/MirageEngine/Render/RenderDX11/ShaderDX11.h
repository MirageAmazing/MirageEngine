#pragma once
#include <d3d11.h>
#include "../Render/Shader.h"

namespace Mirage {
	namespace Render {
		
		using namespace std;

		class ShaderDX11 :public Shader {
		public:
			ShaderDX11(ShaderType type, ID3DBlob* ):Shader(type) {

			}
		private:
			ID3DBlob* mByteCode;
		};
	}
}