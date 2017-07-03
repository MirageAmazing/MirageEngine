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
	TVector2 operator * (float);
	TVector2 operator / (const TVector2&);
	TVector2 operator / (float);
	float operator | (const TVector2&);
	bool operator == (const TVector2&) const;
	void operator += (const TVector2&);
	void operator -= (const TVector2&);

	bool Normalize();
	float Length();

	static float Dot(const TVector2&, const TVector2&);

	float x, y;
};