#pragma once
#include "Vector3.h"
#include "Rotater.h"
#include "Matrix.h"
#include "MEMath.h"
using namespace MirageMath;

namespace MirageMath
{
	template<class T>
	struct Quaternion
	{
	public:
		Quaternion() {
		}
		Quaternion(T InX, T InY, T InZ, T InW):
			x(InX), y(InY), z(InZ), w(InW){

		}
		Quaternion(const Quaternion& InValue) :
			x(InValue.x), y(InValue.y), z(InValue.z), w(InValue.w){

		}
		Quaternion(const Vector3<T>& InAxis, const T InDegree) {
			auto halfDegree = InDegree*0.5;
			auto reciprocal = 1.0 / sqrt(InAxis.x*InAxis.x + InAxis.y*InAxis.y + InAxis.z*InAxis.z);
			x = InAxis.x*sin(halfDegree)*reciprocal;
			y = InAxis.y*sin(halfDegree)*reciprocal;
			z = InAxis.z*sin(halfDegree)*reciprocal;
			w = cos(halfDegree);

			Normalize();
		}
		Quaternion(T InPitch, T InYaw, T InRoll)
		{
			SetEular(InPitch, InYaw, InRoll);
		}

		Quaternion operator * (const Quaternion& InValue) const {
			/*
			// Meth 1: 最直接的四元数乘法
			T tempx = w*InValue.x + x*InValue.w + y*InValue.z - z*InValue.y;
			T tempy = w*InValue.y + y*InValue.w + z*InValue.x - x*InValue.z;
			T tempz = w*InValue.z + z*InValue.w + x*InValue.y - y*InValue.x;
			T tempw = w*InValue.w - x*InValue.x - y*InValue.y - z*InValue.z;
			*/

			/*
			Meth 2: 将四元数看成（v，s）一个向量和一个标量
			Q1(v1, s1) * Q2(v2, s2) = s1*s2-Dot(v1, v2)+ s1*v2 + s2*v1 + Cross(v1, v2)
			*/

			Vector3<T> va(x, y, z);
			Vector3<T> vb(InValue.x, InValue.y, InValue.z);

			auto dotValue = Vector3<T>::Dot(va, vb);
			auto crossValue = Vector3<T>::Cross(va, vb);
			auto vertorA = vb*w;
			auto vertorB = va*InValue.w;
			auto scalarValue = w*InValue.w;

			auto scalar = scalarValue - dotValue;
			auto vector = crossValue + vertorA + vertorB;

			return Quaternion(vector.x, vector.y, vector.z, scalar);
		}
		Quaternion operator *= (const Quaternion& InValue)
		{
			auto result = *this * InValue;
			x = result.x;
			y = result.y;
			z = result.z;
			w = result.w;
			return *this;
		}
		Quaternion operator * (const T scale) const
		{
			return Quaternion(x*scale, y*scale, z*scale, w*scale);
		}
		Quaternion operator *= (const T scale)
		{
			x *= scale;
			y *= scale;
			z *= scale;
			w *= scale;
			return *this;
		}
		Quaternion operator / (const T scale)const
		{
			T recip = 1.0f / scale;
			return Quaternion(recip*x, recip*y, recip*z, recip*w);
		}
		Quaternion operator /= (const T scale)
		{
			T recip = 1.0f / scale;
			x *= recip;
			y *= recip;
			z *= recip;
			w *= recip;
			return *this;
		}
		bool operator == (const Quaternion& In) const
		{
			return x == In.x && y == In.y && z == In.z && w == In.w;
		}
		bool operator != (const Quaternion& In) const
		{
			return x != In.x && y != In.y && z != In.z && w != In.w;
		}

		Rotater<T> GetRotater() const
		{
			T pitch, yaw, roll;
			const double Epsilon = 0.0009765625f;
			const double Threshold = 0.5f - Epsilon;
			double test = x*y + w*z;

			if (test < -Threshold || test > Threshold) // 奇异姿态,俯仰角为±90°
			{
				double sign = copysign(1.0, test);

				yaw = 2 * sign * atan2(x, w);
				pitch = sign * (ME_PI / 2.0);
				roll = 0;
			}
			else
			{
				double sx{ x*x }, sy{ y*y }, sz{ z*z };

				roll = atan2(2 * (y*w - z*x), 1 - 2 * (sy + sz));
				pitch = asin(2 * test);
				yaw = atan2(2 * (x*w - y*z), 1 - 2 * (sx + sz));
			}

			return Rotater<T>(pitch, yaw, roll);
		}
		Vector3<T> Eular() const
		{
			return GetRotater().Eular();
		}
		Matrix4x4<T> GetMatrix() const
		{
			Matrix4x4f mat;
			
			T sx{ 2 * x*x }, sy{ 2 * y*y }, sz{ 2 * z*z };
			T sxy{ 2 * x*y }, szw{ 2 * z*w }, sxz{ 2 * x*z }, syw{ 2 * y*w }, syz{ 2 * y*z }, sxw{ 2 * x*w };

			mat[0][0] = 1 - sy - sz;
			mat[0][1] = sxy - szw;
			mat[0][2] = sxz + syw;
			mat[0][3] = 0;
			mat[1][0] = sxy + szw;
			mat[1][1] = 1 - sx - sz;
			mat[1][2] = syz - sxw;
			mat[1][3] = 0;
			mat[2][0] = sxz - syw;
			mat[2][1] = syz + sxw;
			mat[2][2] = 1 - sx - sy;
			mat[2][3] = 0;
			mat[3][0] = 0;
			mat[3][1] = 0;
			mat[3][2] = 0;
			mat[3][3] = 1;

			return mat;
		}

		void SetEular(T InPitch, T InYaw, T InRoll){
			T cy = cosf(InYaw*0.5);
			T sy = sinf(InYaw*0.5);
			T cr = cosf(InRoll*0.5);
			T sr = sinf(InRoll*0.5);
			T cp = cos(InPitch*0.5);
			T sp = sin(InPitch*0.5);

			x = cp * cy * sr + sp * sy * cr;
			y = sp * cy * cr + cp * sy * sr;
			z = cp * sy * cr - sp * cy * sr;
			w = cp * cy * cr - sp * sy * sr;

			Normalize();
		}

		void Normalize()
		{
			T tt = x*x + y*y + z*z + w*w;
			T t = tt != 0 ? sqrtf(tt) : 1;
			t = 1.0 / t;
			x *= t;
			y *= t;
			z *= t;
			w *= t;
		}

		static Quaternion ConvertRotator(Rotater<T>& rotator) {
			return Quaternion(rotator.pitch, rotator.yaw, rotator.roll);
		}
	public:
		T x, y, z, w;
	};

	using Quaternionf = Quaternion<f32>;
	using QuaternionF = Quaternion<f64>;
}