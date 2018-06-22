#pragma once

#include "IResElement.h"
#include "ResShader.h"
#include <string>

namespace Mirage {
	namespace Resource {

		// The resource of shader
		class ResMaterial : public IResElement {
		public:
			ResMaterial(std::string buff) {
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