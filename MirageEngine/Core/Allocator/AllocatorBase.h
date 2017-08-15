#pragma once
#include <list>
#include <algorithm>

template<class T>
class AllocatorBase
{
public:
	static T* Get(size_t size)
	{
		T* alloctor = new T(size);
		alloctorList.push_back(alloctor);
		return alloctor;
	}
	static bool Delete(T* instance)
	{
		auto endIter = alloctorList.cend();
		if (std::find(alloctorList.cbegin(), endIter, instance)
			!= endIter)
		{
			delete instance;
			alloctorList.remove(instance);
			return true;
		}
		return false;
	}
private:
	static std::list<T*> alloctorList;
};

template<class T>
std::list<T*> AllocatorBase<T>::alloctorList;
