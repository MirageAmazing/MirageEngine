#pragma once
#include <string>
#include <memory>
#include "../Math/MEMath.h"
#include "../Math/VersionNumber.h"
using namespace std;

namespace Mirage
{
	/**
	 * @brief The interface of System
	 */
	class ISystem {
	public:
		virtual void Initialize() {};
		virtual void UnInitialize() {};
		virtual void Tick() {};
		virtual bool IsInitialize() { return false; };
		virtual bool IsBeShutdown() { return false; };
		virtual string GetSystemName() { return ""; };
	};

	/**
	 * /brief The base of all system
	 */
	template<class T>
	class System : ISystem
	{
	public:		
		static shared_ptr<T> GetInstance()
		{
			if (mBeShutdown)
				return nullptr;
			if (mSystem == nullptr)
			{
				mSystem = make_shared<T>();
				mSystem->Initialize();
			}
			return mSystem;
		}

		virtual string GetSystemName() override {
			return typeid(*this).name();
		}
		virtual void Initialize() {
			mIsInitialize = true;
		}
		virtual void UnInitialize(){
			mBeShutdown = true;
		}
		virtual void Tick() {}

		void Shutdown()
		{
			if (mSystem != nullptr)
			{
				UnInitialize();
				delete mSystem;
				mSystem == nullptr;
			}
		}

		MEINLINE virtual bool IsInitialize() override {
			return mIsInitialize;
		}
		MEINLINE virtual bool IsBeShutdown() override {
			return mBeShutdown;
		}

	protected:
		System() 
		{
			//mUID = MirageMath::GenerateUID();
		}
		virtual ~System()
		{
			if (mSystem != nullptr)
				mSystem->UnInitialize();
		}

		Mirage::Math::VersionNumber mVersion;
		MEUID mUID;

	private:
		static shared_ptr<T> mSystem;
		static bool mIsInitialize;
		static bool mBeShutdown;
	};

	template<class T>
	shared_ptr<T> System<T>::mSystem = nullptr;

	template<class T>
	bool System<T>::mIsInitialize = false;

	template<class T>
	bool System<T>::mBeShutdown = false;

	#define FromISystemType(T) typename enable_if<is_base_of<ISystem, T>::value, T>::type

}