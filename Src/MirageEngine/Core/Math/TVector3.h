#pragma once

struct TVector3
{
public:
	TVector3();
	explicit TVector3(float);
	TVector3(float, float, float);
	TVector3(const TVector3&);

	void operator = (const TVector3&);
	TVector3 operator + (const TVector3&) const;
	TVector3 operator - (const TVector3&) const;
	TVector3 operator - () const;
	TVector3 operator * (const TVector3&) const;
	TVector3 operator * (float) const;
	TVector3 operator / (const TVector3&) const;
	float operator | (const TVector3&) const;
	TVector3 operator ^ (const TVector3&) const;
	bool operator == (const TVector3&) const;
	void operator += (const TVector3&);
	void operator -= (const TVector3&);

	bool Normalize();
	TVector3 GetNormal() const;
	float Length() const;

	static float Dot(const TVector3&, const TVector3&);
	static TVector3 Cross(const TVector3&, const TVector3&);

	static const TVector3 Zero;
	static const TVector3 Up;
	static const TVector3 Down;
	static const TVector3 Right;
	static const TVector3 Left;
	static const TVector3 Front;
	static const TVector3 Back;

	float x, y, z;
};

inline TVector3 operator * (const float InValue, const TVector3& InVec)
{
	return InVec*InValue;
}

inline TVector3 operator / (const float InValue, const TVector3& InVec)
{
	return TVector3(
		InVec.x == 0 ? 0 : (InValue / InVec.x),
		InVec.y == 0 ? 0 : (InValue / InVec.y),
		InVec.z == 0 ? 0 : (InValue / InVec.z)
	);
}