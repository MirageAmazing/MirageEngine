#pragma once

#include "IResElement.h"
#include "ResShader.h"
#include <string>

namespace Mirage {
	namespace Resource {

		// The resource of shader
		class ResMaterial : public IResElement {
		public:
			ResMaterial():IResElement(eResElementType::Material){
				
			}

		private:
		};

	}
}