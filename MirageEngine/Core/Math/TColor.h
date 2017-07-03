#pragma once
#include "TVector4.h"

struct TColor
{
public:
	TColor();
	TColor(float InR, float InG, float InB, float InA);
	TColor(float InR, float InG, float InB);
	TColor(const TColor& InValue);
	TColor(const TVector4& InValue);

	void operator = (const TColor& InValue);
	bool operator == (const TColor& InValue) const;

	float r = 0, g = 0, b = 0, a = 1;
};