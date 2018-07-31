#include "MMalloc.h"

namespace Mirage {
	namespace Core {

		MMalloc globalMMalloc;

		MMalloc& GetGlobalMalloc() {
			return globalMMalloc;
		}
	}
}