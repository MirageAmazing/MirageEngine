#pragma once
#include "TVector3.h"

struct TQuaternion
{
public:
	TQuaternion();
	TQuaternion(float InX, float InY, float InZ, float InW);
	TQuaternion(const TQuaternion& InValue);
	TQuaternion(const TVector3& InAxis, const float InDegree);

	TQuaternion operator * (const TQuaternion& InValue) const;
	
	float x, y, z, w;
};