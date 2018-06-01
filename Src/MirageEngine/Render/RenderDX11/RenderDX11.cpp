#include "MirageEngine.h"
#if defined(MIRAGE_PLATFORM_WINDOWS)

#include "RenderDX11.h"
#include "d3dcompiler.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace Mirage {
	namespace Render {
		RenderDX11::RenderDX11(int iScreenWidth, int iScreenHeight, void* pWindowHandle) :
			Render(iScreenWidth, iScreenHeight, pWindowHandle)
		{
			if (pWindowHandle == nullptr)
			{
				// TODO: Exception
				return;
			}
			
			mHwnd = (HWND)pWindowHandle;

			EnvirmentCheck();
			LoadShader();
		}

		RenderDX11::~RenderDX11()
		{
			if (mSwapChain)
			{
				mSwapChain->SetFullscreenState(false, NULL);
			}

			if (mRasterizerState)
			{
				mRasterizerState->Release();
				mRasterizerState = 0;
			}

			if (mDepthStencilView)
			{
				mDepthStencilView->Release();
				mDepthStencilView = 0;
			}

			if (mDepthStencilState)
			{
				mDepthStencilState->Release();
				mDepthStencilState = 0;
			}

			if (mDepthStencilBuffer)
			{
				mDepthStencilBuffer->Release();
				mDepthStencilBuffer = 0;
			}

			if (mRTView)
			{
				mRTView->Release();
				mRTView = 0;
			}

			if (mDeviceContext)
			{
				mDeviceContext->Release();
				mDeviceContext = 0;
			}

			if (mDevice)
			{
				mDevice->Release();
				mDevice = 0;
			}

			if (mSwapChain)
			{
				mSwapChain->Release();
				mSwapChain = 0;
			}
		}

		bool RenderDX11::EnvirmentCheck()
		{
			HRESULT result;
			IDXGIFactory* factory;
			IDXGIAdapter* adapter;
			IDXGIOutput* output;
			unsigned int numModes, i, numerator, denominator, stringLength;
			DXGI_MODE_DESC* displayModeList;
			DXGI_ADAPTER_DESC adapterDesc;
			int error;
			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			D3D_FEATURE_LEVEL featureLevel;
			ID3D11Texture2D* backBufferPtr;
			D3D11_TEXTURE2D_DESC depthBufferDesc;
			D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
			D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
			D3D11_RASTERIZER_DESC rasterDesc;
			D3D11_VIEWPORT viewport;
			float fieldOfView, screenAspect;

			result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
			if (FAILED(result))
			{
				return false;
			}
			result = factory->EnumAdapters(0, &adapter);//video card
			if (FAILED(result))
			{
				return false;
			}
			result = adapter->EnumOutputs(0, &output);//monitor
			if (FAILED(result))
			{
				return false;
			}

			// Get and match displaymode
			result = output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
			if (FAILED(result))
			{
				return false;
			}
			displayModeList = new DXGI_MODE_DESC[numModes];
			if (displayModeList == nullptr)
			{
				return false;
			}
			result = output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
			if (FAILED(result))
			{
				return false;
			}
			for (i = 0; i < numModes; i++)
			{
				if (displayModeList[i].Width == (unsigned int)mRenderWidth)
				{
					if (displayModeList[i].Height == (unsigned int)mRenderHeight)
					{
						numerator = displayModeList[i].RefreshRate.Numerator;
						denominator = displayModeList[i].RefreshRate.Denominator;
					}
				}
			}

			result = adapter->GetDesc(&adapterDesc);
			if (FAILED(result))
			{
				return false;
			}
			mVideoCardMemory = adapterDesc.DedicatedVideoMemory / 1024 / 1024;

			delete[] displayModeList;
			output->Release();
			output = nullptr;
			adapter->Release();
			adapter = nullptr;
			factory->Release();
			factory = nullptr;

			ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
			swapChainDesc.BufferCount = 1;
			swapChainDesc.BufferDesc.Width = mRenderWidth;
			swapChainDesc.BufferDesc.Height = mRenderHeight;
			swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapChainDesc.BufferDesc.RefreshRate.Numerator = mVsyncEnabled ? numerator : 0;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = mVsyncEnabled ? denominator : 1;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.OutputWindow = mHwnd;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.Windowed = !mFullScreen;
			swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.Flags = 0;

			featureLevel = D3D_FEATURE_LEVEL_11_0;

			result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1,
				D3D11_SDK_VERSION, &swapChainDesc, &mSwapChain, &mDevice, nullptr, &mDeviceContext);
			if (FAILED(result))
			{
				return false;
			}

			result = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
			if (FAILED(result))
			{
				return false;
			}
			result = mDevice->CreateRenderTargetView(backBufferPtr, nullptr, &mRTView);
			if (FAILED(result))
			{
				return false;
			}
			backBufferPtr->Release();
			backBufferPtr = nullptr;

			ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
			depthBufferDesc.Width = mRenderWidth;
			depthBufferDesc.Height = mRenderHeight;
			depthBufferDesc.MipLevels = 1;
			depthBufferDesc.ArraySize = 1;
			depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthBufferDesc.SampleDesc.Count = 1;
			depthBufferDesc.SampleDesc.Quality = 0;
			depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthBufferDesc.CPUAccessFlags = 0;
			depthBufferDesc.MiscFlags = 0;

			result = mDevice->CreateTexture2D(&depthBufferDesc, nullptr, &mDepthStencilBuffer);
			if (FAILED(result))
			{
				return false;
			}

			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
			// Depth
			depthStencilDesc.DepthEnable = true;
			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
			// Stencil
			depthStencilDesc.StencilEnable = true;
			depthStencilDesc.StencilReadMask = 0xFF;
			depthStencilDesc.StencilWriteMask = 0xFF;
			// Stencil operations if pixel is front-facing.
			depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			// Stencil operations if pixel is back-facing.
			depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			result = mDevice->CreateDepthStencilState(&depthStencilDesc, &mDepthStencilState);
			if (FAILED(result))
			{
				return false;
			}

			ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
			depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			depthStencilViewDesc.Texture2D.MipSlice = 0;

			result = mDevice->CreateDepthStencilView(mDepthStencilBuffer, &depthStencilViewDesc, &mDepthStencilView);
			if (FAILED(result))
			{
				return false;
			}

			//--------------------------------------Preparing resource over-----------------------------------------

			mDeviceContext->OMSetRenderTargets(1, &mRTView, mDepthStencilView);

			rasterDesc.AntialiasedLineEnable = true;
			rasterDesc.CullMode = D3D11_CULL_BACK;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0;
			rasterDesc.DepthClipEnable = true;
			rasterDesc.FillMode = D3D11_FILL_SOLID;
			rasterDesc.FrontCounterClockwise = false;
			rasterDesc.MultisampleEnable = true;
			rasterDesc.ScissorEnable = true;
			rasterDesc.SlopeScaledDepthBias = 0;

			result = mDevice->CreateRasterizerState(&rasterDesc, &mRasterizerState);
			if (FAILED(result))
			{
				return false;
			}

			mDeviceContext->RSSetState(mRasterizerState);

			viewport.Width = (float)mRenderWidth;
			viewport.Height = (float)mRenderHeight;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			viewport.TopLeftX = 0.0f;
			viewport.TopLeftY = 0.0f;

			mDeviceContext->RSSetViewports(1, &viewport);



			return true;
		}

		void RenderDX11::OnSetClearColor()
		{

		}
		
		HRESULT RenderDX11::CompileShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint, _In_ LPCSTR profile, _Outptr_ ID3DBlob** blob)
		{
			if (!srcFile || !entryPoint || !profile || !blob)
				return E_INVALIDARG;

			*blob = nullptr;

			UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
			flags |= D3DCOMPILE_DEBUG;
#endif

			const D3D_SHADER_MACRO defines[] =
			{
				"EXAMPLE_DEFINE", "1",
				NULL, NULL
			};

			ID3DBlob* shaderBlob = nullptr;
			ID3DBlob* errorBlob = nullptr;
			HRESULT hr = D3DCompileFromFile(srcFile, defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
				entryPoint, profile,
				flags, 0, &shaderBlob, &errorBlob);
			if (FAILED(hr))
			{
				if (errorBlob)
				{
					OutputDebugStringA((char*)errorBlob->GetBufferPointer());
					errorBlob->Release();
				}

				if (shaderBlob)
					shaderBlob->Release();

				return hr;
			}

			*blob = shaderBlob;

			return hr;
		}
	
		void RenderDX11::LoadShader() {
			ID3DBlob *vsBuff = nullptr;
			ID3DBlob *psBuff = nullptr;
			CompileShader(L"../../MirageEngine/Resource/Shader/basic.HLSL", "VS", "vs_5_0", &vsBuff);
			CompileShader(L"../../MirageEngine/Resource/Shader/basic.HLSL", "PS", "ps_5_0", &psBuff);

			mDevice->CreateVertexShader(vsBuff->GetBufferPointer(), vsBuff->GetBufferSize(), nullptr, &mVexterShader);
			mDevice->CreatePixelShader(psBuff->GetBufferPointer(), psBuff->GetBufferSize(), nullptr, &mPixelShader);

			D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
			polygonLayout[0].SemanticName = "POSITION";
			polygonLayout[0].SemanticIndex = 0;
			polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			polygonLayout[0].InputSlot = 0;
			polygonLayout[0].AlignedByteOffset = 0;
			polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[0].InstanceDataStepRate = 0;

			polygonLayout[1].SemanticName = "COLOR";
			polygonLayout[1].SemanticIndex = 0;
			polygonLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			polygonLayout[1].InputSlot = 0;
			polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			polygonLayout[1].InstanceDataStepRate = 0;

			auto numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

			mDevice->CreateInputLayout(polygonLayout, numElements, vsBuff->GetBufferPointer(), vsBuff->GetBufferSize(), &mLayout);

			vsBuff->Release();
			psBuff->Release();
		}

		void RenderDX11::Frame()
		{
			float clearColor[4];
			clearColor[0] = mClearColor[0];
			clearColor[1] = mClearColor[1];
			clearColor[2] = mClearColor[2];
			clearColor[3] = 1.0f;
			mDeviceContext->ClearRenderTargetView(mRTView, clearColor);
			mDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);


			mSwapChain->Present(mVsyncEnabled ? 1 : 0, 0);
		}
	}
}
#endif