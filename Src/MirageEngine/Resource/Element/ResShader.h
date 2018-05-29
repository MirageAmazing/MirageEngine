#pragma once
#include "IResElement.h"
#include <string>

namespace Mirage {
	namespace Resource {
		
		// The resource of shader
		class ResShader : public IResElement{
		public:
			ResShader(std::string buff) {
				mElementType = eResElementType::Shader;
				mBuff = buff;
			}

			std::string Buff() {
				return mBuff;
			}

		private:
			std::string mBuff;
		};

	}
}