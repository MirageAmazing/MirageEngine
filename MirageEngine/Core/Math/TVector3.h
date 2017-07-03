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
	TVector3 operator / (float) const;
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

	static TVector3 Zero;
	static TVector3 Up;
	static TVector3 Down;
	static TVector3 Right;
	static TVector3 Left;
	static TVector3 Front;
	static TVector3 Back;

	float x, y, z;
};