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

			void operator = (const Transform& transform) {
				translation = transform.translation;
				scale = transform.scale;
				rotation = transform.rotation;
			}

			Matrix4x4f GetTransformMatrix() const
			{
				auto t = Matrix4x4f::Translate(translation);
				auto r = rotation.GetMatrix();
				auto s = Matrix4x4f::Scale(scale);

				return s*r*t;
			}

			MEINLINE void SetTranslation(const Vector3f& t){
				translation = t;
			}
			MEINLINE void SetTranslation(f32 x, f32 y, f32 z) {
				translation.x = x;
				translation.y = y;
				translation.z = z;
			}
			MEINLINE void AddTranslation(const Vector3f& t) {
				translation += t;
			}
			MEINLINE void AddTranslation(f32 x, f32 y, f32 z) {
				translation.x += x;
				translation.y += y;
				translation.z += z;
			}
			MEINLINE Vector3f GetTranslation() const{
				return translation;
			}
			MEINLINE void SetScale(const Vector3f& s) {
				scale = s;
			}
			MEINLINE void SetScale(f32 x, f32 y, f32 z) {
				scale.x = x;
				scale.y = y;
				scale.z = z;
			}
			MEINLINE void SetScale(f32 v) {
				scale.x = v;
				scale.y = v;
				scale.z = v;
			}
			MEINLINE void AddScale(const Vector3f& s) {
				scale += s;
			}
			MEINLINE void AddScale(f32 v) {
				scale.x += v;
				scale.y += v;
				scale.z += v;
			}
			MEINLINE void AddScale(f32 x, f32 y, f32 z) {
				scale.x += x;
				scale.y += y;
				scale.z += z;
			}
			MEINLINE Vector3f GetScale() const{
				return scale;
			}
			MEINLINE void SetRotate(f32 x, f32 y, f32 z) {
				rotation.SetEular(x, y, z);
			}
			MEINLINE void SetRotate(const Quaternionf& quat) {
				rotation = quat;
			}
			MEINLINE void AddRotate(f32 x, f32 y, f32 z) {
				rotation *= Quaternionf::ConvertRotator(Rotaterf(x, y, z));
			}
			MEINLINE Quaternionf GetRotate() const{
				return rotation;
			}

		private:
			Vector3f translation;
			Vector3f scale;
			Quaternionf rotation;
		};

	}
}
