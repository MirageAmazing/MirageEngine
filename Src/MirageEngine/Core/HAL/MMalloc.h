#pragma once
#include "jemalloc/jemalloc.h"
#include "Platform.h"
#include <atomic>
#include <memory>
using namespace std;

namespace Mirage {
	namespace Core {
		/**
		 * /brief The malloc for Mirage, I'll use jemalloc as the basic malloc.
		 */
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

			template<class T, class... _Types>
			MEINLINE shared_ptr<T> MakeShared(_Types&&... _Args) {
				return new shared_ptr<T>(New(_Args), Delete);
			}

			template<class T, class... _Types>
			MEINLINE unique_ptr<T> MakeUnique(_Types&&... _Args) {
				return new unique_ptr<T>(New(_Args), Delete);
			}

		protected:
			static atomic<uint32> CurrentAllocSize;
		};

		/**
		 * /brief The global malloc for Mirage.
		 */
		MMalloc mmalloc;
	}
}