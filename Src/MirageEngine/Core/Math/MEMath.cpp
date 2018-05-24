#include "MEMath.h"

namespace MirageMath
{
	//generate guid
	MEUID uid{ 0 };
	MEUID GenerateUID()
	{
		return uid++;
	}
}