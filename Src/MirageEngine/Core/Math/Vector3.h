#pragma once
#include "../Core.h"
#include <cmath>

namespace MirageMath
{
	template<class T> struct Vector3
	{
	public:
		Vector3() = default;
		explicit Vector3(T In)
		{
			x = In;
			y = In;
			z = In;
		}
		Vector3(T InX, T InY, T InZ)
		{
			x = InX;
			y = InY;
			z = InZ;
		}
		Vector3(const Vector3& In)
		{
			x = In.x;
			y = In.y;
			z = In.z;
		}

		void operator = (const Vector3& InV)
		{
			x = InV.x;
			y = InV.y;
			z = InV.z;
		}
		Vector3 operator + (const Vector3& InV) const
		{
			return Vector3(x + InV.x, y + InV.y, z + InV.z);
		}
		Vector3 operator - (const Vector3& InV) const
		{
			return Vector3(x - InV.x, y - InV.y, z - InV.z);
		}
		Vector3 operator - () const
		{
			return Vector3(-x, -y, -z);
		}
		Vector3 operator * (const Vector3& InV) const
		{
			return Vector3(x * InV.x, y * InV.y, z * InV.z);
		}
		Vector3 operator * (T In) const
		{
			return Vector3(x * In, y * In, z * In);
		}
		Vector3 operator / (const Vector3& InV) const
		{
			return Vector3(x / InV.x, y / InV.y, z / InV.z);
		}
		float operator | (const Vector3& In) const
		{
			return x*In.x + y*In.y + z*In.z;
		}
		Vector3 operator ^ (const Vector3& In) const
		{
			return Vector3(
				y*In.z - z*In.y,
				z*In.x - x*In.z,
				x*In.y - y*In.x
			);
		}
		bool operator == (const Vector3& InValue) const
		{
			return (x == InValue.x) && (y == InValue.y) && (z == InValue.z);
		}
		void operator += (const Vector3& InV)
		{
			x += InV.x;
			y += InV.y;
			z += InV.z;
		}
		void operator -= (const Vector3& InV)
		{
			x -= InV.x;
			y -= InV.y;
			z -= InV.z;
		}

		bool Normalize()
		{
			auto length = Length();
			if (length == 0)
				return false;
			auto reciprocal = 1.0 / length;
			x *= reciprocal;
			y *= reciprocal;
			z *= reciprocal;
			return true;
		}
		Vector3 GetNormal() const
		{
			auto length = Length();
			if (length == 0)
				return Zero;

			Vector3 result = *this;
			result.Normalize();

			return result;
		}
		T Length() const
		{
			return std::sqrt(x*x + y*y + z*z);
		}

		static float Dot(const Vector3<T>& InA, const Vector3<T>& InB)
		{
			return InA | InB;
		}
		static Vector3<T> Cross(const Vector3<T>& InA, const Vector3<T>& InB)
		{
			return InA^InB;
		}

		static const Vector3<T> Zero;
		static const Vector3<T> Up;
		static const Vector3<T> Down;
		static const Vector3<T> Right;
		static const Vector3<T> Left;
		static const Vector3<T> Front;
		static const Vector3<T> Back;

		T x=0, y=0, z=0;
	};

	template<class T> const Vector3<T> Vector3<T>::Zero = Vector3<T>(0, 0, 0);
	template<class T> const Vector3<T> Vector3<T>::Up = Vector3<T>(0, 1, 0);
	template<class T> const Vector3<T> Vector3<T>::Down = Vector3<T>(0, -1, 0);
	template<class T> const Vector3<T> Vector3<T>::Right = Vector3<T>(-1, 0, 0);
	template<class T> const Vector3<T> Vector3<T>::Left = Vector3<T>(1, 0, 0);
	template<class T> const Vector3<T> Vector3<T>::Front = Vector3<T>(0, 0, 1);
	template<class T> const Vector3<T> Vector3<T>::Back = Vector3<T>(0, 0, -1);

	template<class T, class F>
	MEINLINE Vector3<T> operator * (const F InValue, const Vector3<T>& InVec)
	{
		return InVec*InValue;
	}
	template<class T, class F>
	MEINLINE Vector3<T> operator / (const F InValue, const Vector3<T>& InVec)
	{
		return Vector3<T>(
			InVec.x == 0 ? 0 : (InValue / InVec.x),
			InVec.y == 0 ? 0 : (InValue / InVec.y),
			InVec.z == 0 ? 0 : (InValue / InVec.z)
		);
	}

	typedef Vector3<f32> Vector3f;
	typedef Vector3<f64> Vector3F;
}