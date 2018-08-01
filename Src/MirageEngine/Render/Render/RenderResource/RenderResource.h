#pragma once

namespace Mirage {
	namespace Render {
	
		class RenderResource {
		public:
			RenderResource() {}
			virtual ~RenderResource() {}

			virtual void InitResource() {}
			virtual void ReleaseResource() {}

			bool IsInitialize() {
				return mIsInitialize;
			}
			bool IsRelease() {
				return mIsRelease;
			}

		protected:
			bool mIsInitialize = false;
			bool mIsRelease = false;
		};

	}
}