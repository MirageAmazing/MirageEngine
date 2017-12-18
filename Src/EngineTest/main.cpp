#include <iostream>
#include <new>
#include <chrono>
#include <future>

#include "../MirageEngine/Core/Math/TQuaternion.h"
#include "../MirageEngine/Core/Math/TVector3.h"
#include "../MirageEngine/Core/Allocator/Allocator.h"
#include "../MirageEngine/Core/HAL/IOBase.h"
#include "EngineTest.h"
#include "EngineTestClass.h"

using namespace std;
using Vector = TVector3;

int main(int argsCount, char** args)
{
	EnvironmentInfo();

	auto r = std::async(std::launch::async, []() {
		cout << "Hello, std::async!" << endl;
		return "Async";
	});
	cout<< r.get() <<endl;

	char buff[50];
	void* pBuff = (void*)buff;
	size_t size = 0;
	if (FileIOSystem::Get().LoadFile("../../Resource/file.bin", buff, 50, size))
	{
		cout << "Loaded Successfully!" << endl;
	}
	FileIOSystem::Get().SaveFileAsync("../../Resource/saveAsync.bin", buff, size, [](bool r) {
		if(r)
			cout << "Save Successfully!" << endl;
	});
	FileIOSystem::Get().SaveFileAsync("../../Resource/saveAsync1.bin", buff, size, [](bool r) {
		if (r)
			cout << "Save Successfully 1!" << endl;
	});
	FileIOSystem::Get().SaveFileAsync("../../Resource/saveAsync2.bin", buff, size, [](bool r) {
		if (r)
			cout << "Save Successfully! 2" << endl;
	});
	FileIOSystem::Get().SaveFileAsync("../../Resource/saveAsync3.bin", buff, size, [](bool r) {
		if (r)
			cout << "Save Successfully! 3" << endl;
	});
	
	Print(sizeof(int));
	Print(sizeof(void*));

	
	
	auto vecPool = new PoolAllocator<MyClass>(20);
	auto v1 = vecPool->Allocte(23, 89, 21);
	auto v2 = vecPool->Allocte(7, 849, 212);
	auto v3 = vecPool->Allocte(65, 89, 21);
	auto vr = *v1 + *v2;

	cout <<"Memery test:"<< vr.x << " " << vr.y << " " << vr.z << endl;

	vecPool->Free(v1);
	vecPool->Free(v2);
	vecPool->Free(v3);
	
	system("Pause");
	return 0;
}