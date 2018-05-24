#pragma once
#include "../Math/MEMath.h"

namespace Mirage
{
	template<class T>
	class ISystem
	{
	public:		
		static T* GetInstance()
		{
			if (mSystem == nullptr)
			{
				mSystem = new T();
				mSystem->Initialize();
			}
			return mSystem;
		}

		virtual void Initialize() {}
		virtual void UnInitialize(){}
		void Shutdown()
		{
			if (mSystem != nullptr)
			{
				UnInitialize();
				delete mSystem;
				mSystem == nullptr;
			}
		}

	protected:
		ISystem() 
		{
			mUID = MirageMath::GenerateUID();
		}
		virtual ~ISystem()
		{
			if (mSystem != nullptr)
				mSystem->UnInitialize();
		}

		MirageMath::VersionNumber mVersion;
		MEUID mUID;

	private:
		static T* mSystem;
	};

	template<class T>
	T* ISystem<T>::mSystem = nullptr;
}