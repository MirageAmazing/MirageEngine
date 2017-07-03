#include "TQuaternion.h"
#include <cmath>

TQuaternion::TQuaternion()
{

}

TQuaternion::TQuaternion(float InX, float InY, float InZ, float InW) :
	x(InX), y(InY), z(InZ), w(InW)
{

}

TQuaternion::TQuaternion(const TQuaternion& InValue):
	x(InValue.x), y(InValue.y), z(InValue.z), w(InValue.w)
{

}

TQuaternion::TQuaternion(const TVector3& InAxis, const float InDegree)
{
	auto halfDegree = InDegree*0.5;
	x = InAxis.x*sin(halfDegree);
	y = InAxis.y*sin(halfDegree);
	z = InAxis.z*sin(halfDegree);
	w = cos(halfDegree);
}

TQuaternion TQuaternion::operator * (const TQuaternion& InValue) const
{
	TQuaternion result;

	//result.x = 
}