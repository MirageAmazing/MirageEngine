#include "TColor.h"
#include <cmath>

TColor::TColor()
{
	r = 0;
	g = 0;
	b = 0;
	a = 1;
}

TColor::TColor(float InR, float InG, float InB, float InA)
{
	r = InR;
	g = InG;
	b = InB;
	a = InA;
}

TColor::TColor(float InR, float InG, float InB)
{
	r = InR;
	g = InG;
	b = InB;
	a = 1;
}

TColor::TColor(const TVector4& InValue)
{
	r = InValue.x;
	g = InValue.y;
	b = InValue.z;
	a = InValue.w;
}

TColor::TColor(const TColor& InValue)
{
	r = InValue.r;
	g = InValue.g;
	b = InValue.b;
	a = InValue.a;
}

void TColor ::operator  = (const TColor& InValue) 
{
	r = InValue.r;
	g = InValue.g;
	b = InValue.b;
	a = InValue.a;
}

bool TColor ::operator  == (const TColor& InValue) const
{
	return (r == InValue.r) && (g == InValue.g) && (b == InValue.b) && (a == InValue.a);
}