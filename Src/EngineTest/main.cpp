#include <iostream>
#include <new>
#include <chrono>
#include <future>

#include "../MirageEngine/Core/Math/TQuaternion.h"
#include "../MirageEngine/Core/Math/TVector3.h"
#include "../MirageEngine/Core/Allocator/Allocator.h"
#include "../MirageEngine/Core/HAL/IOBase.h"
#include "../MirageEngine/Core/HAL/Platform.h"

using namespace std;
using Vector = TVector3;

#define Print(x) cout<<x<<endl

class Alloctor
{
public:
	static Alloctor* Instance() 
	{
		if (mInstance == nullptr)
			mInstance = new Alloctor(1024);
		return mInstance;
	}
	void* alloctor(size_t size)
	{
		auto pResult = mPointer;
		mPointer += size;
		return pResult;
	}

private:
	Alloctor(size_t size)
	{
		mMemory = (char*)malloc(size);
		mPointer = mMemory;
	}
	~Alloctor()
	{
		free(mMemory);
	}

	
private:
	char* mPointer;
	char* mMemory;
	static Alloctor* mInstance;
};
Alloctor* Alloctor::mInstance = nullptr;

template<class T>
class MyAlloctor
{
public:
	MyAlloctor(){}

	T* allocte(int count)
	{
		auto pArray = (T*)Alloctor::Instance()->alloctor(count*sizeof(T));
		return pArray;
	}

	template<class... _Types>
	void construct(T* pObj, _Types&&... _Args) 
	{
		new(pObj) T(forward<_Types>(_Args)...);
	}
};

class MyClass
{
public:
	MyClass()
	{
		x = 0;
		y = 0;
	}
	MyClass(double ix, double iy)
	{
		x = ix;
		y = iy;
	}
	MyClass(double ix, double iy, double iz)
	{
		x = ix;
		y = iy;
		z = iz;
	}
	MyClass operator + (const MyClass& InV) const
	{
		return MyClass(x + InV.x, y + InV.y, z + InV.z);
	}

	double x = 0;
	double y = 0;
	double z = 0;
};

class FreeList
{
private:
	struct FreeListNode
	{
		FreeListNode(size_t size)
		{
			memory = malloc(size);
		}
		~FreeListNode()
		{
			free(memory);
		}
		size_t sizeofMemory;
		void* memory;
		FreeListNode* previous = nullptr;
		FreeListNode* next = nullptr;
	};
public:
	FreeList() {}
	~FreeList() {}

	FreeListNode* Allocate(size_t size)
	{
		FreeListNode* node = new FreeListNode(size);
		if (freeListNode == nullptr)
		{
			freeListNode = node;
		}
		else
		{
			node->previous = freeListNode;
			freeListNode->next = node;
			freeListNode = node;
		}
		return node;
	}
	bool ReAllocate(FreeListNode* node)
	{
		auto pointer = freeListNode;
		if (pointer == nullptr)
			return false;

		do
		{
			if (pointer == node)
			{
				auto preNode = pointer->previous;
				auto nextNode = pointer->next;
				if(preNode != nullptr)preNode->next = nextNode;
				if(nextNode != nullptr)nextNode->previous = preNode;
				delete node;
				return true;
			}
			pointer = pointer->previous;
		} while (pointer != nullptr);

		return false;
	}

private:
	FreeListNode* freeListNode = nullptr;
};

// int supports_AVX()
// {
// 	__asm
// 	{
// 		mov eax, 1
// 		cpuid
// 		and ecx, 018000000H
// 		cmp ecx, 018000000H //check both OSXSAVE and AVX feature flags
// 		jne not_supported
// 		//; processor supports AVX instructions and XGETBV is enabled by OS
// 		mov ecx, 0 // specify 0 for XCR0 register
// 		XGETBV //result in EDX : EAX
// 		and eax, 06H
// 		cmp eax, 06H// check OS has enabled both XMM and YMM state support
// 		jne not_supported
// 		mov eax, 1
// 		jmp done
// 		not_supported:
// 		mov eax, 0
// 		done:
// 	}
// }
// int supports_avx2()
// {
// 	_asm
// 	{
// 		mov eax, 1
// 		cpuid
// 		and ecx, 018000000H
// 		cmp ecx, 018000000H//; check both OSXSAVE and AVX feature flags
// 		jne not_supported
// 		//; processor supports AVX instructions and XGETBV is enabled by OS
// 		mov eax, 7
// 		mov ecx, 0
// 		cpuid
// 		and ebx, 20H
// 		cmp ebx, 20H//; check AVX2 feature flags
// 		jne not_supported
// 		mov ecx, 0//; specify 0 for XFEATURE_ENABLED_MASK register
// 		XGETBV//; result in EDX : EAX
// 		and eax, 06H
// 		cmp eax, 06H//; check OS has enabled both XMM and YMM state support
// 		jne not_supported
// 		mov eax, 1
// 		jmp done
// 		not_supported :
// 		mov eax, 0
// 		done :
// 	}
// }


int main(int argsCount, char** args)
{
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

	#if defined(MIRAGE_COMPILER_CLANG)
		Print("CLANG");
	#elif defined(MIRAGE_COMPILER_GNUC)
		Print("GCC");
	#elif defined(MIRAGE_COMPILER_MSVC)
		Print("MSVC");
	#else
		#error Unsupported compiler was used.
	#endif
	
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