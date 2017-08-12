#pragma once
#include "MemoryPool.h"
#include "AllocatorBase.h"
#include <memory>
#include <cassert>

template<class T>
class PoolAllocator:public AllocatorBase<PoolAllocator<T>>
{
	typedef struct FreeListNode
	{
		FreeListNode(T* m)
		{
			memoryNode = m;
		}
		T* memoryNode = nullptr;
		FreeListNode* next;
	}*FreeList,*PFreeListNode;

public:
	PoolAllocator(size_t count) 
	{
		auto size = sizeof(T);
		Assert(size >= sizeof(FreeListNode));

		memory = MemoryPool::Get()->Allocate(count*sizeof(T));
		auto memoryStart = memory->memory;
		FreeList tempfl = nullptr;
		for (size_t i = 0; i < count; i++)
		{
			FreeList fl = (FreeList)memoryStart;
			PFreeListNode flPointer = new(fl) FreeListNode((T*)memoryStart);
			if (freeList == nullptr)
				freeList = flPointer;
			else
				tempfl->next = flPointer;
			tempfl = flPointer;
			memoryStart = (void*)((int)memoryStart+size);
		}
	}
	~PoolAllocator() 
	{
		MemoryPool::Get()->ReAllocate(memory);
	}

	template<class... _Types>
	T* Allocte(_Types&&... _Args)
	{
		if (freeList == nullptr)
			return nullptr;

		auto memoryNode = freeList->memoryNode;
		freeList = freeList->next;

		T* pObj = (T*)memoryNode;
		return new(pObj) T(forward<_Types>(_Args)...);
	}

	bool Free(T* pObj)
	{
		unsigned int memoryAddress = (unsigned int)(memory->memory);
		unsigned int objAddress = (unsigned int)pObj;
		if (objAddress >= memoryAddress && objAddress < (memoryAddress + memory->sizeofMemory))
		{
			FreeList fl = (FreeList)objAddress;
			auto flPointer = new(fl) FreeListNode(pObj);
			flPointer->next = freeList;
			freeList = flPointer;
			return true;
		}
		return false;
	}

private:
	template<class... _Types>
	void construct(T* pObj, _Types&&... _Args)
	{
		new(pObj) T(forward<_Types>(_Args)...);
	}

private:
	FreeList freeList = nullptr;
	MemoryPool::Memory* memory = nullptr;
};