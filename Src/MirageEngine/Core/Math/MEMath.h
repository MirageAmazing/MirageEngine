#pragma once
#include <cmath>
#include <string>
#include "../Core.h"

namespace MirageMath
{
	#define ME_E			2.71828182845904523536   // e
	#define ME_LOG2E		1.44269504088896340736   // log2(e)
	#define ME_LOG10E		0.434294481903251827651  // log10(e)
	#define ME_LN2			0.693147180559945309417  // ln(2)
	#define ME_LN10			2.30258509299404568402   // ln(10)
	#define ME_PI			3.14159265358979323846   // pi
	#define ME_PI_2			1.57079632679489661923   // pi/2
	#define ME_PI_4			0.785398163397448309616  // pi/4
	#define ME_1_PI			0.318309886183790671538  // 1/pi
	#define ME_2_PI			0.636619772367581343076  // 2/pi
	#define ME_2_SQRTPI		1.12837916709551257390   // 2/sqrt(pi)
	#define ME_SQRT2		1.41421356237309504880   // sqrt(2)
	#define ME_SQRT1_2		0.707106781186547524401  // 1/sqrt(2)

	MEINLINE f32 DegreeToRadians(float degree) { return degree*ME_PI / 180.0f; }
	MEINLINE f32 RadiansToDegree(float radians) { return radians*180.0f / ME_PI; }
	
	const f32 F32NAN = nanf("");
	const f64 F64NAN = nan("");

	//generate guid
	extern MEINLINE MEUID GenerateUID();
}