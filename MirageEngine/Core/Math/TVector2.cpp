#include "TVector2.h"
#include <cmath>

TVector2::TVector2()
{
	x = 0;
	y = 0;
}

TVector2::TVector2(float InX, float InY)
{
	x = InX;
	y = InY;
}

void TVector2::operator = (const TVector2& InV)
{
	x = InV.x;
	y = InV.y;
}

TVector2 TVector2::operator + (const TVector2& InV)
{
	return TVector2(x + InV.x, y + InV.y);
}

TVector2 TVector2::operator - (const TVector2& InV)
{
	return TVector2(x - InV.x, y - InV.y);
}

TVector2 TVector2::operator * (const TVector2& InV)
{
	return TVector2(x * InV.x, y * InV.y);
}

TVector2 TVector2::operator * (const float In) const
{
	return TVector2(x * In, y * In);
}

TVector2 TVector2::operator / (const TVector2& InV)
{
	return TVector2(x / InV.x, y / InV.y);
}

float TVector2::operator | (const TVector2& In) const
{
	return x*In.x + y*In.y;
}

bool TVector2::operator == (const TVector2& InValue) const
{
	return (x == InValue.x) && (y == InValue.y);
}

void TVector2::operator += (const TVector2& InV)
{
	x += InV.x;
	y += InV.y;
}

void TVector2::operator -= (const TVector2& InV)
{
	x -= InV.x;
	y -= InV.y;
}

bool TVector2::Normalize()
{
	auto length = Length();
	if (length == 0)
		return false;
	x /= length;
	y /= length;
	return true;
}

float TVector2::Length()
{
	return std::sqrt(x*x + y*y);
}

float TVector2::Dot(const TVector2& InA, const TVector2& InB)
{
	return InA | InB;
}