#pragma once

#include "../MirageEngine.h"
#include "../Core/Math/MEMath.h"

namespace Mirage{
	namespace Resource {
		class ResMesh;

		/*
		 Type of resource
		*/
		enum class eResElementType{
			Mesh,
			Texture,
			Audio,

			Count,
			None
		};

		/*
		 Basic type of resouce element.
		*/
		class IResElement
		{
		public:
			MEINLINE eResElementType GetType() { return mElementType; }

			IResElement(ResMesh&) {}

		protected:
			IResElement()
			{
				mGuid = MirageMath::GenerateUID();
			}
			virtual ~IResElement() {}

			eResElementType mElementType{ eResElementType::None };
		private:
			MEUID mGuid;
		};
	}
}