#include <iostream>
#include <new>
#include <chrono>
#include <future>

#include "../MirageEngine/Core/Math/TQuaternion.h"
#include "../MirageEngine/Core/Math/TVector3.h"
#include "../MirageEngine/Core/Allocator/MemoryPool.h"
#include "../MirageEngine/Core/Allocator/Allocator.h"
#include "../MirageEngine/Core/HAL/IOBase.h"

using namespace std;
using Vector = TVector3;

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
	MyClass(int ix, int iy)
	{
		x = ix;
		y = iy;
	}
	MyClass(int ix, int iy, float iz)
	{
		x = ix;
		y = iy;
		z = iz;
	}

	int x = 0;
	int y = 0;
	float z = 0;
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
	if (FileIOSystem::Get().LoadFile("file.bin", buff, 50, size))
	{
		cout << "Loaded Successfully!" << endl;
	}
	FileIOSystem::Get().SaveFileAsync("saveAsync.bin", buff, size, [](bool r) {
		cout << "Save Successfully!" << endl;
	});
	FileIOSystem::Get().SaveFileAsync("saveAsync1.bin", buff, size, [](bool r) {
		cout << "Save Successfully 1!" << endl;
	});
	FileIOSystem::Get().SaveFileAsync("saveAsync2.bin", buff, size, [](bool r) {
		cout << "Save Successfully! 2" << endl;
	});
	FileIOSystem::Get().SaveFileAsync("saveAsync3.bin", buff, size, [](bool r) {
		cout << "Save Successfully! 3" << endl;
	});

	TVector3 v1(12,45,89);
	TVector3 v2(22,45,89);
	auto v3 = v1+v2;
	cout<<v3.x<<" "<<v3.y<<" "<<v3.z<<endl;
	
	return 0;
}