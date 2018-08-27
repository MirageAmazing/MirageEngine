#pragma once

using namespace std;

namespace Mirage {
	namespace DesignPattern {
		/*
		* The Singleton pattern
		*/
		template<class T>
		class Singleton {
		public:
			template<class... Args>
			static T* Instance(Args&&... args) {
				if (_instance == nullptr)
				{
					_instance = new T(forward<Args>(args)...);
				}
				return _instance;
			}

			virtual void Initialize() {
				isInitialize = true;
			}
			virtual void UnInitialize() {
				isUnInitialize = true;
			}

			bool IsInitialize() {
				return isInitialize;
			}
			bool IsUnInitialize() {
				return isUnInitialize;
			}

		private:
			bool isInitialize = false;
			bool isUnInitialize = false;

			static T* _instance;
		};

		template<class T>
		T* Singleton<T>::_instance = nullptr;
	}
}