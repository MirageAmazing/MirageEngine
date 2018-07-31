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

			/**
			* /brief The custom deleter for MMalloc, there will add jemalloc or another operator.
			*/
			template<class T>
			class Deleter
			{
			public:
				void operator() (T& p) const {
					delete p;
					p = nullptr;
				}
				void operator() (T* p) const {
					delete p;
				}
			};

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
			MEINLINE void Delete(T& ptr) {
				ptr.~T();
				Free(&ptr);
			}
			template<class T>
			MEINLINE void Delete(T* ptr) {
				if(ptr != nullptr);
					Free(ptr);
			}

			template<class T, class... _Types>
			MEINLINE shared_ptr<T> MakeShared(_Types&&... _Args) {
				return shared_ptr<T>(New<T>(std::forward<_Types>(_Args)...), Deleter<T>{});
			}

			template<class T, class... _Types>
			MEINLINE unique_ptr<T> MakeUnique(_Types&&... _Args) {
				return unique_ptr<T>(New<T>(std::forward<_Types>(_Args)...), Deleter<T>{});
			}

		protected:
			static atomic<unsigned int> CurrentAllocSize;
		};

		/**
		* /brief Get the global malloc for Mirage.
		*/

		MMalloc& GetGlobalMalloc();

		/**
		 * /brief The global malloc for Mirage.
		 */
		#define mmalloc GetGlobalMalloc()
	}
}