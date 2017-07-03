#pragma once

struct TVector2
{
public:
	TVector2();
	TVector2(float, float);

	void operator = (const TVector2&);
	TVector2 operator + (const TVector2&);
	TVector2 operator - (const TVector2&);
	TVector2 operator * (const TVector2&);
	TVector2 operator * (const float) const;
	TVector2 operator / (const TVector2&);
	float operator | (const TVector2&) const;
	bool operator == (const TVector2&) const;
	void operator += (const TVector2&);
	void operator -= (const TVector2&);

	bool Normalize();
	float Length();

	static float Dot(const TVector2&, const TVector2&);

	float x, y;
};

TVector2 operator * (const float InValue, const TVector2& InVec)
{
	return InVec*InValue;
}

TVector2 operator / (const float InValue, const TVector2& InVec)
{
	return TVector2(
		InVec.x == 0 ? 0 : (InValue / InVec.x),
		InVec.y == 0 ? 0 : (InValue / InVec.y)
	);
}