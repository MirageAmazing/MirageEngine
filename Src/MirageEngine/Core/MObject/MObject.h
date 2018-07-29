#pragma once
#include <string>
#include "../Core.h"

namespace Mirage {

	using namespace std;

	/**
	* @brief	The core object for the metaobject system.
	*/
	class MObject {
	public:
		MObject() {}
		~MObject() {}

		string GetTypeName() const { return typeid(*this).name(); };
		virtual void Initialize() { isInitialized = true; }
		virtual void Destory() { isDestory = true; }
		bool IsInitialized() { return isInitialized; }
		bool IsDestory() { return isDestory; }

		virtual void Serialize() { }

	private:
		bool isInitialized = false;
		bool isDestory = false;
	};

}