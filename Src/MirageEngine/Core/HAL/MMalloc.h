#pragma once
#include "jemalloc/jemalloc.h"
#include "Platform.h"
#include <atomic>
using namespace std;

namespace Mirage {
	namespace Core {

		class MMalloc {
		public:
			MMalloc() {}
			~MMalloc() {}

			MEINLINE void* Malloc(size_t size) {
				return malloc(size);
			}
			MEINLINE void Free(void* ptr) {
				free(ptr);
			}
			template<class T, class... _Types>
			MEINLINE T* New(_Types&&... _Args) {
				auto ptr = Malloc(sizeof(T));
				return new(ptr) T(std::forward<_Types>(_Args)...);
			}
			template<class T>
			MEINLINE void Delete(T* ptr) {
				if (ptr != nullptr)
					ptr->~T();
				Free(ptr);
			}

		protected:
			static atomic<uint32> CurrentAllocSize;
		};

	}
}