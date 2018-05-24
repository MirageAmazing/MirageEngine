#pragma once
#include "Vector3.h"
#include "Quaternion.h"

namespace Mirage{
	namespace Math {

		class Transform {
		public:
			Transform() : translation(0), scale(1), rotation(0, 0, 0)
			{
			}
			Transform(Transform& in)
			{
				translation = in.translation;
				scale = in.scale;
				rotation = in.rotation;
			}
			~Transform() {}

			Matrix4x4f GetTransformMatrix() const
			{
				auto t = Matrix4x4f::Translate(translation);
				auto r = rotation.GetMatrix();
				auto s = Matrix4x4f::Scale(scale);

				return s*r*t;
			}

			void SetTranslation(Vector3f t){
				translation = t;
			}
			void SetTranslation(f32 x, f32 y, f32 z) {
				translation.x = x;
				translation.y = y;
				translation.z = z;
			}
			void AddTranslation(Vector3f t) {
				translation += t;
			}
			void AddTranslation(f32 x, f32 y, f32 z) {
				translation.x += x;
				translation.y += y;
				translation.z += z;
			}
			Vector3f GetTranslation(){
				return translation;
			}
			void SetScale(Vector3f s) {
				scale = s;
			}
			void SetScale(f32 x, f32 y, f32 z) {
				scale.x = x;
				scale.y = y;
				scale.z = z;
			}
			void AddScale(Vector3f s) {
				scale += s;
			}
			void AddScale(f32 x, f32 y, f32 z) {
				scale.x += x;
				scale.y += y;
				scale.z += z;
			}
			Vector3f GetScale() {
				return scale;
			}
			void SetRotate(f32 x, f32 y, f32 z) {
				rotation.SetEular(x, y, z);
			}
			void AddRotate(f32 x, f32 y, f32 z) {
				rotation *= Quaternionf::ConvertRotator(Rotaterf(x, y, z));
			}
			Quaternionf GetRotate() {
				return rotation;
			}

		private:
			Vector3f translation;
			Vector3f scale;
			Quaternionf rotation;
		};

	}
}
