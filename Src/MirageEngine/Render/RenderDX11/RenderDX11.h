#pragma once
#include "MirageEngine.h"
#if defined(MIRAGE_PLATFORM_WINDOWS)

#include "../Render/Render.h"
#include <memory>
#include <dxgi.h>
#include <d3d11.h>
#include "../Core/Math/Camera.h"
#include "../Core/Math/Transform.h"

namespace Mirage {
	namespace Render {

		using namespace std;
		using namespace Mirage::Math;

		class RenderDX11 :public Render{
		public :
			static ID3D11Device* GetCurrentDevice() {
				return mCurrentRedner == nullptr ? nullptr : mCurrentRedner->mDevice;
			}

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
			ID3D11VertexShader* mVexterShader{nullptr};
			ID3D11PixelShader* mPixelShader{ nullptr };
			ID3D11InputLayout* mLayout{ nullptr };
			ID3D11Buffer *mVertexBuffer{ nullptr }, *mIndexBuffer{ nullptr }, *mMatrixBuffer{ nullptr };
			std::unique_ptr<Camera> mCamera;
			Transform mTransform;
			//temp->

			HWND mHwnd;

			ID3D11Device* mDevice;
			ID3D11DeviceContext* mDeviceContext;
			IDXGISwapChain* mSwapChain;
			ID3D11RenderTargetView* mRTView;
			ID3D11Texture2D* mDepthStencilBuffer;
			ID3D11DepthStencilState* mDepthStencilState;
			ID3D11DepthStencilView* mDepthStencilView;
			ID3D11RasterizerState* mRasterizerState;

			static RenderDX11* mCurrentRedner;
		};
	}
}
#endif