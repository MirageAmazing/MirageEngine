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
	TVector4 operator / (float) const;
	bool operator == (TVector4&) const;
	void operator += (TVector4&);
	void operator -= (TVector4&);


	float x, y, z, w;
};