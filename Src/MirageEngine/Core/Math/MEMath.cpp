#include "MEMath.h"

namespace Mirage{
	namespace Math {
		//generate guid
		MEUID uid{ 0 };
		MEUID GenerateUID()
		{
			return uid++;
		}
	}
}