#pragma once
#include "MirageEngine.h"
#include <string>
#include <tuple>
#include <memory>

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

			ErrorType
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
			Shader() {
			}			
			~Shader() {
			}

		private:
		};

		template<class VS, class HS, class DS, class GS, class PS>
		class ShaderContainer :Shader {
		public:
			ShaderContainer(shared_ptr<VS> vs, shared_ptr<HS> hs, shared_ptr<DS> ds, shared_ptr<GS> gs, shared_ptr<PS> ps) :
				Shader() {
				mVs = vs;
				mHs = hs;
				mDs = ds;
				mGs = gs;
				mPs = ps;
			}

			MEINLINE shared_ptr<VS> GetVertexShader() {
				return mVs;
			}
			MEINLINE shared_ptr<HS> GetHullShader() {
				return mHs;
			}
			MEINLINE shared_ptr<DS> GetDomainShader() {
				return mDs;
			}
			MEINLINE shared_ptr<GS> GetGeometryShader() {
				return mGs;
			}
			MEINLINE shared_ptr<PS> GetPixelShader() {
				return mPs;
			}

		private:
			shared_ptr<VS> mVs;
			shared_ptr<HS> mHs;
			shared_ptr<DS> mDs;
			shared_ptr<GS> mGs;
			shared_ptr<PS> mPs;
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

		/*
		The result of complie shader
		*/
		class ShaderComplieResult {
		public:
			ShaderComplieResult() {
				mType = ShaderType::ErrorType;
			}
			ShaderComplieResult(ShaderType type) {
				mType = type;
			}
			ShaderComplieResult(ShaderComplieResult& in) {
				mType = in.mType;
			}
			virtual ~ShaderComplieResult() {
			}

			ShaderType GetType() {
				return mType;
			}
		protected:
			ShaderType mType;
		};

		using ShaderComplieResult_Ptr = shared_ptr<ShaderComplieResult>;
	}
}