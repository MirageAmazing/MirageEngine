#pragma once
#include "../Format/TextureFormat.h"
#include "IResElement.h"

namespace Mirage {
	namespace Resource {
		class ResTexture :public IResElement
		{
		public:
			ResTexture():IResElement(eResElementType::Texture) {
			}
		};
	}
}