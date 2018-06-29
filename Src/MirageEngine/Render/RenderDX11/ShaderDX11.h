#pragma once
#include <memory>
#include <d3d11.h>
#include "../Render/Shader.h"
#include "../RenderDX11/RenderDX11.h"

namespace Mirage {
	namespace Render {
		
		using namespace std;

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
					device->CreateVertexShader(bc.get()->GetBufferPointer(), bc.get()->GetBufferSize(), nullptr, &shader);
					mVertexShader = make_shared<ID3D11HullShader>(shader);
				}
			}
		private:
			shared_ptr<ID3D11HullShader> mVertexShader;
		};

	}
}