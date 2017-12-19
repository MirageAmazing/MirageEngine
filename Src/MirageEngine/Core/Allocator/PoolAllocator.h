#pragma once
#include "../HAL/Platform.h"
#include "MemoryPool.h"
#include "AllocatorBase.h"
#include <memory>
#include <cassert>
#include <utility>

template<class T>
class PoolAllocator:public AllocatorBase<PoolAllocator<T>>
{
	typedef struct ListNode
	{
		ListNode()
		{
		}
		T memoryNode;
		ListNode* next = nullptr;
	}*PListNode,*PFreeListNode,*PUsedListNode;

public:
	PoolAllocator(size_t count) 
	{
		size_t sizeNodeBody = sizeof(T);
		size_t sizeNodeHeader = sizeof(PListNode);
		size_t sizeNode = sizeof(ListNode);
		assert(sizeNodeBody >= sizeNodeHeader);

		memory = MemoryPool::Get()->Allocate(count*(sizeNode));
		auto memoryStart = memory->memory;
		PListNode tempfl = nullptr;
		for (size_t i = 0; i < count; i++)
		{
			PListNode fl = (PListNode)memoryStart;
			auto flPointer = new(fl) ListNode();
			if (freeList == nullptr)
				freeList = flPointer;
			else
				tempfl->next = flPointer;
			tempfl = flPointer;
			memoryStart = (void*)((size_t)(memoryStart)+ sizeNode);
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

		auto currentNode = freeList;
		auto memoryNode = &(currentNode->memoryNode);
		
		freeList = freeList->next;

		if (usedList == nullptr)
		{
			usedList = currentNode;
			usedList->next = nullptr;
		}
		else
		{
			currentNode->next = usedList;
			usedList = currentNode;
		}

		return new(memoryNode) T(std::forward<_Types>(_Args)...);
	}

	/**
	 * Free object in this pool.
	 *
	 * @param pObj Object that we need free.
	 */
	bool Free(T* pObj)
	{
		auto memoryAddress = (size_t)(memory->memory);
		auto objAddress = (size_t)pObj;
		if (objAddress >= memoryAddress && objAddress < (memoryAddress + memory->sizeofMemory))
		{
			PListNode prePointer = nullptr;			
			PListNode pointer = usedList;
			while (pointer != nullptr)
			{
				if ((&(pointer->memoryNode)) == pObj)
				{
					if (prePointer != nullptr)
						prePointer->next = pointer->next;
					else
						usedList = usedList->next;

					pointer = new (pointer) ListNode();
					pointer->next = freeList;
					freeList = pointer;

					return true;
				}
				prePointer = pointer;
				pointer = pointer->next;
			}
		}
		return false;
	}

private:
	template<class... _Types>
	void construct(T* pObj, _Types&&... _Args)
	{
		new(pObj) T(std::forward<_Types>(_Args)...);
	}

private:
	PListNode freeList = nullptr;
	PListNode usedList = nullptr;
	MemoryPool::Memory* memory = nullptr;
};