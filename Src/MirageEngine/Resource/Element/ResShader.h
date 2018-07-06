#pragma once
#include "IResElement.h"
#include "../../Render/RenderSystem.h"
#include <string>

namespace Mirage {
	namespace Resource {
		
		using namespace Mirage::Render;

		// The resource of shader
		class ResShader : public IResElement{
		public:
			ResShader(std::string buff, ShaderType type):IResElement(eResElementType::Shader) {
				mBuff = buff;
				mShaderType = type;

				mShaderComplieResult = RenderSystem::GetInstance()->ComplieShader(mBuff, mShaderType);
			}

			std::string Buff() {
				return mBuff;
			}
			ShaderComplieResult_Ptr GetComplieResult() {
				return mShaderComplieResult;
			}

		private:
			ShaderComplieResult_Ptr mShaderComplieResult;

			ShaderType mShaderType;
			std::string mBuff;
		};

	}
}