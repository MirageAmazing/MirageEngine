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
			VertexShaderDX11(shared_ptr<ID3DBlob> bc):VertexShader(){
				auto device = RenderDX11::GetCurrentDevice();
				if (device != nullptr)
				{
					ID3D11VertexShader* vertexShader = nullptr;
					device->CreateVertexShader(bc.get()->GetBufferPointer(), bc.get()->GetBufferSize(), nullptr, &vertexShader);
					mVertexShader = make_shared<ID3D11VertexShader>(vertexShader);
				}
			}
			shared_ptr<ID3D11VertexShader> GetShader() {
				return mVertexShader;
			}
		private:
			shared_ptr<ID3D11VertexShader> mVertexShader;
		};

		class HullShaderDX11 :public HullShader {
		public:
			HullShaderDX11(shared_ptr<ID3DBlob> bc) :HullShader() {
				auto device = RenderDX11::GetCurrentDevice();
				if (device != nullptr)
				{
					ID3D11HullShader* shader = nullptr;
					device->CreateHullShader(bc.get()->GetBufferPointer(), bc.get()->GetBufferSize(), nullptr, &shader);
					mHullShader = make_shared<ID3D11HullShader>(shader);
				}
			}
			shared_ptr<ID3D11HullShader> GetShader() {
				return mHullShader;
			}
		private:
			shared_ptr<ID3D11HullShader> mHullShader;
		};

		class DomainShaderDX11 :public DomainShader {
		public:
			DomainShaderDX11(shared_ptr<ID3DBlob> bc) :DomainShader() {
				auto device = RenderDX11::GetCurrentDevice();
				if (device != nullptr)
				{
					ID3D11DomainShader* shader = nullptr;
					device->CreateDomainShader(bc.get()->GetBufferPointer(), bc.get()->GetBufferSize(), nullptr, &shader);
					mDomainShader = make_shared<ID3D11DomainShader>(shader);
				}
			}
			shared_ptr<ID3D11DomainShader> GetShader() {
				return mDomainShader;
			}
		private:
			shared_ptr<ID3D11DomainShader> mDomainShader;
		};

		class GeometryShaderDX11 :public GeometryShader {
		public:
			GeometryShaderDX11(shared_ptr<ID3DBlob> bc) :GeometryShader() {
				auto device = RenderDX11::GetCurrentDevice();
				if (device != nullptr)
				{
					ID3D11GeometryShader* shader = nullptr;
					device->CreateGeometryShader(bc.get()->GetBufferPointer(), bc.get()->GetBufferSize(), nullptr, &shader);
					mGeometryShader = make_shared<ID3D11GeometryShader>(shader);
				}
			}
			shared_ptr<ID3D11GeometryShader> GetShader() {
				return mGeometryShader;
			}
		private:
			shared_ptr<ID3D11GeometryShader> mGeometryShader;
		};

		class PixelShaderDX11 :public PixelShader {
		public:
			PixelShaderDX11(shared_ptr<ID3DBlob> bc) :PixelShader() {
				auto device = RenderDX11::GetCurrentDevice();
				if (device != nullptr)
				{
					ID3D11PixelShader* shader = nullptr;
					device->CreatePixelShader(bc.get()->GetBufferPointer(), bc.get()->GetBufferSize(), nullptr, &shader);
					mPixelShader = make_shared<ID3D11PixelShader>(shader);
				}
			}
			shared_ptr<ID3D11PixelShader> GetShader() {
				return mPixelShader;
			}
		private:
			shared_ptr<ID3D11PixelShader> mPixelShader;
		};

		class ComputeShaderDX11 :public ComputeShader {
		public:
			ComputeShaderDX11(shared_ptr<ID3DBlob> bc) :ComputeShader() {
				auto device = RenderDX11::GetCurrentDevice();
				if (device != nullptr)
				{
					ID3D11ComputeShader* shader = nullptr;
					device->CreateComputeShader(bc.get()->GetBufferPointer(), bc.get()->GetBufferSize(), nullptr, &shader);
					mComputeShader = make_shared<ID3D11ComputeShader>(shader);
				}
			}
			shared_ptr<ID3D11ComputeShader> GetShader() {
				return mComputeShader;
			}
		private:
			shared_ptr<ID3D11ComputeShader> mComputeShader;
		};

		class ShaderComplieResultDX11 :public ShaderComplieResult {
		public:
			ShaderComplieResultDX11(ShaderType type, bool isNormal, shared_ptr<ID3DBlob> shader, shared_ptr<ID3DBlob> errorInfo):
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
			shared_ptr<ID3DBlob> Shader() {
				return mShader;
			}
			shared_ptr<ID3DBlob> ErrorInfo() {
				return mErrorInfo;
			}
		private:
			bool mIsNormal;
			shared_ptr<ID3DBlob> mShader;
			shared_ptr<ID3DBlob> mErrorInfo;
		};

		using ShaderComplieResultDX11_Ptr = shared_ptr<ShaderComplieResultDX11>;
	}
}