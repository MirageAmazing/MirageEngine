#pragma once
#include <string>
#include <tuple>

namespace Mirage {
	namespace Render {

		using namespace std;

		/*
		The type of shader
		*/
		enum class ShaderType {
			VertexShader,
			HullShader,
			DomainShader,
			GeometryShader,
			PixelShader,
			ComputeShader,
		};
		class VertexShader;
		class HullShader;
		class DomainShader;
		class GeometryShader;
		class PixelShader;
		class ComputeShader;

		/*
		The complex shader contain all stage.
		*/
		class Shader {
		public:
			Shader(tuple<VertexShader, PixelShader> shaders) {
			}
			Shader(tuple<VertexShader, HullShader, DomainShader, GeometryShader, PixelShader> shaders) {
			}
			~Shader() {
			}

		private:
		};

		/*
		Define the base of shader
		*/
		class BaseShader {
		public:
			BaseShader(ShaderType shaderType) {
				mShaderType = shaderType;
			}
			virtual ~BaseShader() {}

		protected:
			ShaderType mShaderType;
		};

		class VertexShader :BaseShader {
		public:
			VertexShader():BaseShader(ShaderType::VertexShader) {}
		};
			
		class HullShader :BaseShader {
		public:
			HullShader() :BaseShader(ShaderType::HullShader) {}
		};

		class DomainShader :BaseShader {
		public:
			DomainShader() :BaseShader(ShaderType::DomainShader) {}
		};

		class GeometryShader :BaseShader {
		public:
			GeometryShader() :BaseShader(ShaderType::GeometryShader) {}
		};

		class PixelShader :BaseShader {
		public:
			PixelShader() :BaseShader(ShaderType::PixelShader) {}
		};

		class ComputeShader :BaseShader {
		public:
			ComputeShader() :BaseShader(ShaderType::ComputeShader) {}
		};
	}
}