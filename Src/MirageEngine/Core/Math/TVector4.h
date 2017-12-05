#pragma once

struct TVector4
{
public:
	TVector4();
	TVector4(float, float, float);
	TVector4(float, float, float, float);

	void operator = (TVector4&);
	TVector4 operator + (TVector4&) const;
	TVector4 operator - (TVector4&) const;
	TVector4 operator * (TVector4&) const;
	TVector4 operator * (float) const;
	TVector4 operator / (TVector4&) const;
	bool operator == (TVector4&) const;
	void operator += (TVector4&);
	void operator -= (TVector4&);

	float x, y, z, w;
};

TVector4 operator * (const float InValue, const TVector4& InVec)
{
	return InVec*InValue;
}

TVector4 operator / (const float InValue, const TVector4& InVec)
{
	return TVector4(
		InVec.x == 0 ? 0 : (InValue / InVec.x),
		InVec.y == 0 ? 0 : (InValue / InVec.y),
		InVec.z == 0 ? 0 : (InValue / InVec.z),
		InVec.w == 0 ? 0 : (InValue / InVec.w)
	);
}