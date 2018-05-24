#pragma once
#include "../Core.h"

namespace MirageMath
{
	template<class T> struct Vector4
	{
	public:
		Vector4() = default;
		Vector4(T InX, T InY, T InZ)
		{
			x = InX;
			y = InY;
			z = InZ;
			w = 1;
		}
		Vector4(T InX, T InY, T InZ, T InW)
		{
			x = InX;
			y = InY;
			z = InZ;
			w = InW;
		}
		Vector4(T In)
		{
			x = In;
			y = In;
			z = In;
			w = In;
		}

		void operator = (Vector4& InV)
		{
			x = InV.x;
			y = InV.y;
			z = InV.z;
			w = InV.w;
		}
		Vector4 operator + (Vector4& InV) const
		{
			return Vector4(x + InV.x, y + InV.y, z + InV.z, w + InV.w);
		}
		Vector4 operator - (Vector4& InV) const
		{
			return Vector4(x - InV.x, y - InV.y, z - InV.z, w - InV.w);
		}
		Vector4 operator * (Vector4& InV) const
		{
			return Vector4(x * InV.x, y * InV.y, z * InV.z, w*InV.w);
		}
		Vector4 operator * (T In) const
		{
			return Vector4(x * In, y * In, z * In, w*In);
		}
		Vector4 operator / (Vector4& InV) const
		{
			return Vector4(x / InV.x, y / InV.y, z / InV.z, w / InV.w);
		}
		bool operator == (Vector4& InValue) const
		{
			return (x == InValue.x) && (y == InValue.y) && (z == InValue.z) && (w == InValue.w);
		}
		void operator += (Vector4& InV)
		{
			x += InV.x;
			y += InV.y;
			z += InV.z;
			w += InV.w;
		}
		void operator -= (Vector4& InV)
		{
			x -= InV.x;
			y -= InV.y;
			z -= InV.z;
			w -= InV.w;
		}

		T x=0, y=0, z=0, w=0;
	};

	template<class T, class F>
	MEINLINE Vector4<T> operator * (const F InValue, const Vector4<T>& InVec)
	{
		return InVec*InValue;
	}
	template<class T, class F>
	MEINLINE Vector4<T> operator / (const F InValue, const Vector4<T>& InVec)
	{
		return Vector4<T>(
			InVec.x == 0 ? 0 : (InValue / InVec.x),
			InVec.y == 0 ? 0 : (InValue / InVec.y),
			InVec.z == 0 ? 0 : (InValue / InVec.z),
			InVec.w == 0 ? 0 : (InValue / InVec.w)
		);
	}

	typedef Vector4<f32> Vector4f;
	typedef Vector4<f64> Vector4F;
}