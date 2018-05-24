#pragma once

#include "../BaseRender/BaseRender.h"

#if defined(MIRAGE_PLATFORM_WINDOWS)

#include <dxgi.h>
#include <d3d11.h>

#pragma comment(lib, "dxgi.lib")

namespace Mirage {
	namespace Render {
		class RenderDX11 :public BaseRender{
		public:
			RenderDX11(int iScreenWidth, int iScreenHeight, void* pWindowHandle);
			~RenderDX11();

			void Frame() override;

		protected:
			bool EnvirmentCheck() override;
			void OnSetClearColor() override;

		private:
			HWND mHwnd;

			IDXGISwapChain* mSwapChain;
			ID3D11Device* mDevice;
			ID3D11DeviceContext* mDeviceContext;
			ID3D11RenderTargetView* mRTView;
			ID3D11Texture2D* mDepthStencilBuffer;
			ID3D11DepthStencilState* mDepthStencilState;
			ID3D11DepthStencilView* mDepthStencilView;
			ID3D11RasterizerState* mRasterizerState;
		};
	}
}
#endif