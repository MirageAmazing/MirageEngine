#pragma once
#include <memory>
#include <d3d11.h>
#include "../Render/Shader.h"
#include "../RenderDX11/RenderDX11.h"

namespace Mirage {
	namespace Render {
		
		using namespace std;

		class VertexShaderDX11;
		class HullShaderDX11;
		class DomainShaderDX11;
		class GeometryShaderDX11;
		class PixelShaderDX11;

		using ShaderDX11 = ShaderContainer<VertexShaderDX11, HullShaderDX11, DomainShaderDX11, GeometryShaderDX11, PixelShaderDX11>;

		class VertexShaderDX11 :public VertexShader {
		public:
			VertexShaderDX11(ID3DBlob* bc):VertexShader(){
				auto device = RenderDX11::GetCurrentDevice();
				if (device != nullptr)
				{
					ID3D11VertexShader* vertexShader = nullptr;
					device->CreateVertexShader(bc->GetBufferPointer(), bc->GetBufferSize(), nullptr, &vertexShader);
					mVertexShader = vertexShader;
				}
			}
			ID3D11VertexShader* GetShader() {
				return mVertexShader;
			}
		private:
			ID3D11VertexShader* mVertexShader;
		};

		class HullShaderDX11 :public HullShader {
		public:
			HullShaderDX11(ID3DBlob* bc) :HullShader() {
				auto device = RenderDX11::GetCurrentDevice();
				if (device != nullptr)
				{
					ID3D11HullShader* shader = nullptr;
					device->CreateHullShader(bc->GetBufferPointer(), bc->GetBufferSize(), nullptr, &shader);
					mHullShader = shader;
				}
			}
			ID3D11HullShader* GetShader() {
				return mHullShader;
			}
		private:
			ID3D11HullShader* mHullShader;
		};

		class DomainShaderDX11 :public DomainShader {
		public:
			DomainShaderDX11(ID3DBlob* bc) :DomainShader() {
				auto device = RenderDX11::GetCurrentDevice();
				if (device != nullptr)
				{
					ID3D11DomainShader* shader = nullptr;
					device->CreateDomainShader(bc->GetBufferPointer(), bc->GetBufferSize(), nullptr, &shader);
					mDomainShader = shader;
				}
			}
			ID3D11DomainShader* GetShader() {
				return mDomainShader;
			}
		private:
			ID3D11DomainShader* mDomainShader;
		};

		class GeometryShaderDX11 :public GeometryShader {
		public:
			GeometryShaderDX11(ID3DBlob* bc) :GeometryShader() {
				auto device = RenderDX11::GetCurrentDevice();
				if (device != nullptr)
				{
					ID3D11GeometryShader* shader = nullptr;
					device->CreateGeometryShader(bc->GetBufferPointer(), bc->GetBufferSize(), nullptr, &shader);
					mGeometryShader = shader;
				}
			}
			ID3D11GeometryShader* GetShader() {
				return mGeometryShader;
			}
		private:
			ID3D11GeometryShader* mGeometryShader;
		};

		class PixelShaderDX11 :public PixelShader {
		public:
			PixelShaderDX11(ID3DBlob* bc) :PixelShader() {
				auto device = RenderDX11::GetCurrentDevice();
				if (device != nullptr)
				{
					ID3D11PixelShader* shader = nullptr;
					device->CreatePixelShader(bc->GetBufferPointer(), bc->GetBufferSize(), nullptr, &shader);
					mPixelShader = shader;
				}
			}
			ID3D11PixelShader* GetShader() {
				return mPixelShader;
			}
		private:
			ID3D11PixelShader* mPixelShader;
		};

		class ComputeShaderDX11 :public ComputeShader {
		public:
			ComputeShaderDX11(ID3DBlob* bc) :ComputeShader() {
				auto device = RenderDX11::GetCurrentDevice();
				if (device != nullptr)
				{
					ID3D11ComputeShader* shader = nullptr;
					device->CreateComputeShader(bc->GetBufferPointer(), bc->GetBufferSize(), nullptr, &shader);
					mComputeShader = shader;
				}
			}
			ID3D11ComputeShader* GetShader() {
				return mComputeShader;
			}
		private:
			ID3D11ComputeShader* mComputeShader;
		};

		class ShaderComplieResultDX11 :public ShaderComplieResult {
		public:
			ShaderComplieResultDX11(ShaderType type, bool isNormal, ID3DBlob* shader, ID3DBlob* errorInfo):
				ShaderComplieResult(type) {
			}
			ShaderComplieResultDX11(ShaderComplieResultDX11& in):ShaderComplieResult(in){
				mIsNormal = in.mIsNormal;
				mShader = in.mShader;
				mErrorInfo = in.mErrorInfo;
			}
			~ShaderComplieResultDX11() {
				mShader->Release();
				mErrorInfo->Release();
			}

			bool IsNormal() {
				return mIsNormal;
			}
			ID3DBlob* Shader() {
				return mShader;
			}
			ID3DBlob* ErrorInfo() {
				return mErrorInfo;
			}
		private:
			bool mIsNormal;
			ID3DBlob* mShader;
			ID3DBlob* mErrorInfo;
		};

		using ShaderComplieResultDX11_Ptr = shared_ptr<ShaderComplieResultDX11>;
	}
}