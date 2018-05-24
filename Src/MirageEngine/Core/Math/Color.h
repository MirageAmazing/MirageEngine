#pragma once
#include "Vector4.h"

namespace MirageMath
{
	template<class T> 
	struct Color
	{
	public:
		Color()
		{
			r = 0;
			g = 0;
			b = 0;
			a = 1;
		}
		Color(T InR, T InG, T InB, T InA)
		{
			r = InR;
			g = InG;
			b = InB;
			a = InA;
		}
		Color(T InR, T InG, T InB)
		{
			r = InR;
			g = InG;
			b = InB;
			a = 1;
		}
		Color(const Color& InValue)
		{
			r = InValue.r;
			g = InValue.g;
			b = InValue.b;
			a = InValue.a;
		}
		Color(const Vector4<T>& InValue)
		{
			r = InValue.x;
			g = InValue.y;
			b = InValue.z;
			a = InValue.w;
		}

		void operator = (const Color& InValue)
		{
			r = InValue.r;
			g = InValue.g;
			b = InValue.b;
			a = InValue.a;
		}
		bool operator == (const Color& InValue) const
		{
			return (r == InValue.r) && (g == InValue.g) && (b == InValue.b) && (a == InValue.a);
		}

		T r = 0, g = 0, b = 0, a = 1;
	};

	using Colorf = Color<f32>;
}