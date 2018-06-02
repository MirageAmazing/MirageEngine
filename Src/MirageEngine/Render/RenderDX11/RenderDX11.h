#pragma once
#include "MirageEngine.h"
#if defined(MIRAGE_PLATFORM_WINDOWS)

#include "../BaseRender/BaseRender.h"
#include <memory>
#include <dxgi.h>
#include <d3d11.h>
#include "../Core/Math/Camera.h"
#include "../Core/Math/Transform.h"

namespace Mirage {
	namespace Render {

		using namespace Mirage::Math;

		class RenderDX11 :public Render{
		public:
			RenderDX11(int iScreenWidth, int iScreenHeight, void* pWindowHandle);
			~RenderDX11();

			void Frame() override;

		protected:
			bool EnvirmentCheck() override;
			void OnSetClearColor() override;
			void LoadShader();
			HRESULT CompileShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint, _In_ LPCSTR profile, _Outptr_ ID3DBlob** blob);

		private:
			//<-temp
			ID3D11VertexShader* mVexterShader;
			ID3D11PixelShader* mPixelShader;
			ID3D11InputLayout* mLayout;
			ID3D11Buffer *mVertexBuffer, *mIndexBuffer, *mMatrixBuffer;
			std::unique_ptr<Camera> mCamera;
			Transform mTransform;
			//temp->


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