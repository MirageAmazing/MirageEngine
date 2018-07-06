#pragma once
#include <memory>
#include <GL\glew.h>
#include "../Render/Shader.h"
#include "../RenderOGL4/RenderOGL4.h"

namespace Mirage {
	namespace Render {

		using namespace std;

		class VertexShaderOGL4;
		class HullShaderOGL4;
		class DomainShaderOGL4;
		class GeometryShaderOGL4;
		class PixelShaderOGL4;

		using ShaderOGL4 = ShaderContainer<VertexShaderOGL4, HullShaderOGL4, DomainShaderOGL4, GeometryShaderOGL4, PixelShaderOGL4>;

		class VertexShaderOGL4 :public VertexShader {
		public:
			VertexShaderOGL4(GLuint shaderID) :VertexShader() {
				mShaderID = shaderID;
			}
			GLuint GetShader() {
				return mShaderID;
			}
		private:
			GLuint mShaderID = 0;
		};

		class HullShaderOGL4 :public HullShader {
		public:
			HullShaderOGL4(GLuint shaderID) :HullShader() {
				mShaderID = shaderID;
			}
			GLuint GetShader() {
				return mShaderID;
			}
		private:
			GLuint mShaderID = 0;
		};

		class DomainShaderOGL4 :public DomainShader {
		public:
			DomainShaderOGL4(GLuint shaderID) :DomainShader() {
				mShaderID = shaderID;
			}
			GLuint GetShader() {
				return mShaderID;
			}
		private:
			GLuint mShaderID = 0;
		};

		class GeometryShaderOGL4 :public GeometryShader {
		public:
			GeometryShaderOGL4(GLuint shaderID) :GeometryShader() {
				mShaderID = shaderID;
			}
			GLuint GetShader() {
				return mShaderID;
			}
		private:
			GLuint mShaderID = 0;
		};

		class PixelShaderOGL4 :public PixelShader {
		public:
			PixelShaderOGL4(GLuint shaderID) :PixelShader() {
				mShaderID = shaderID;
			}
			GLuint GetShader() {
				return mShaderID;
			}
		private:
			GLuint mShaderID = 0;
		};

		class ComputeShaderOGL4 :public ComputeShader {
		public:
			ComputeShaderOGL4(GLuint shaderID) :ComputeShader() {
				mShaderID = shaderID;
			}
			GLuint GetShader() {
				return mShaderID;
			}
		private:
			GLuint mShaderID = 0;
		};

		class ShaderComplieResultOGL4 :public ShaderComplieResult {
		public:
			ShaderComplieResultOGL4(ShaderType type, bool isNormal, GLuint shader, string errorInfo):
				ShaderComplieResult(type) {
			}
			ShaderComplieResultOGL4(ShaderComplieResultOGL4& in):ShaderComplieResult(in){
				mIsNormal = in.mIsNormal;
				mShader = in.mShader;
				mErrorInfo = in.mErrorInfo;
			}
			~ShaderComplieResultOGL4() {
			}

			bool IsNormal() {
				return mIsNormal;
			}
			GLuint Shader() {
				return mShader;
			}
			string ErrorInfo() {
				return mErrorInfo;
			}
		private:
			bool mIsNormal;
			GLuint mShader;
			string mErrorInfo;
		};

		using ShaderComplieResultOGL4_Ptr = shared_ptr<ShaderComplieResultOGL4>;
	}
}