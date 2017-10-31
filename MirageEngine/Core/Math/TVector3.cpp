#include "TVector3.h"
#include <cmath>

TVector3::TVector3()
{
	x = 0;
	y = 0;
	z = 0;
}

TVector3::TVector3(float In)
{
	x = In;
	y = In;
	z = In;
}

TVector3::TVector3(float InX, float InY, float InZ)
{
	x = InX;
	y = InY;
	z = InZ;
}

TVector3::TVector3(const TVector3& In)
{
	x = In.x;
	y = In.y;
	z = In.z;
}

void TVector3::operator = (const TVector3& InV)
{
	x = InV.x;
	y = InV.y;
	z = InV.z;
}

TVector3 TVector3::operator + (const TVector3& InV) const
{
	return TVector3(x + InV.x, y + InV.y, z + InV.z);
}

TVector3 TVector3::operator - (const TVector3& InV) const
{
	return TVector3(x - InV.x, y - InV.y, z - InV.z);	
}

TVector3 TVector3::operator - () const
{
	return TVector3( -x, -y, -z);
}

TVector3 TVector3::operator * (const TVector3& InV) const
{
	return TVector3(x * InV.x, y * InV.y, z * InV.z);
}

TVector3 TVector3::operator * (float In) const
{
	return TVector3(x * In, y * In, z * In);
}

TVector3 TVector3::operator / (const TVector3& InV) const
{
	return TVector3(x / InV.x, y / InV.y, z / InV.z);
}

float TVector3::operator | (const TVector3& In) const
{
	return x*In.x + y*In.y + z*In.z;
}

TVector3 TVector3::operator^(const TVector3& In) const
{
	return TVector3(
		y*In.z-z*In.y,
		z*In.x-x*In.z,
		x*In.y-y*In.x
	);
}

bool TVector3::operator == (const TVector3& InValue) const
{
	return (x == InValue.x) && (y == InValue.y) && (z == InValue.z);
}

void TVector3::operator += (const TVector3& InV)
{
	x += InV.x;
	y += InV.y;
	z += InV.z;
}

void TVector3::operator -= (const TVector3& InV)
{
	x -= InV.x;
	y -= InV.y;
	z -= InV.z;
}

bool TVector3::Normalize()
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

TVector3 TVector3::GetNormal() const
{
	auto length = Length();
	if (length == 0)
		return Zero;

	TVector3 result = *this;
	result.Normalize();

	return result;
}

float TVector3::Length() const
{
	return std::sqrt(x*x + y*y + z*z);
}

float TVector3::Dot(const TVector3& InA, const TVector3& InB)
{
	return InA | InB;
}

TVector3 TVector3::Cross(const TVector3& InA, const TVector3& InB)
{
	return InA^InB;
}

const TVector3 TVector3::Zero = TVector3(0, 0, 0);
const TVector3 TVector3::Up = TVector3(0, 1, 0);
const TVector3 TVector3::Down = TVector3(0, -1, 0);
const TVector3 TVector3::Right = TVector3(-1, 0, 0);
const TVector3 TVector3::Left = TVector3(1, 0, 0);
const TVector3 TVector3::Front = TVector3(0, 0, 1);
const TVector3 TVector3::Back = TVector3(0, 0, -1);
