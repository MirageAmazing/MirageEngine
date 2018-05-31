#pragma once
#include <memory>
#include "../Math/MEMath.h"
#include "../Math/VersionNumber.h"
using namespace std;

namespace Mirage
{
	template<class T>
	class ISystem
	{
	public:		
		static shared_ptr<T> GetInstance()
		{
			if (mSystem == nullptr)
			{
				mSystem = make_shared<T>();
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
			//mUID = MirageMath::GenerateUID();
		}
		virtual ~ISystem()
		{
			if (mSystem != nullptr)
				mSystem->UnInitialize();
		}

		MirageMath::VersionNumber mVersion;
		MEUID mUID;

	private:
		static shared_ptr<T> mSystem;
	};

	template<class T>
	shared_ptr<T> ISystem<T>::mSystem = nullptr;
}