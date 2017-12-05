#pragma once
#include "MemoryPool.h"
#include "AllocatorBase.h"
#include <memory>
#include <list>

class StackAllocator:public AllocatorBase<StackAllocator>
{
public:
	explicit StackAllocator(size_t size)
	{
		memory = MemoryPool::Get()->Allocate(size);
		startPointer = static_cast<char*>(memory->memory);
		endPointer = startPointer+size;
		pointer = startPointer;
	}
	StackAllocator(StackAllocator&& alloctor)
	{
		memory = alloctor.memory;
		startPointer = alloctor.startPointer;
		endPointer = alloctor.endPointer;
		pointer = alloctor.pointer;

		alloctor.memory = nullptr;
		alloctor.startPointer = nullptr;
		alloctor.endPointer = nullptr;
		alloctor.pointer = nullptr;
	}
	~StackAllocator()
	{
		if (pointer != startPointer)
		{
			//TODO:Exception
		}
		MemoryPool::Get()->ReAllocate(memory);
	}

	StackAllocator() = delete;
	StackAllocator& operator = (const StackAllocator&) = delete;

	void* Allocate(size_t size)
	{
		auto result = pointer;
		auto move = pointer+size;
		if (move > endPointer)
		{
			//TODO:Exception
			return nullptr;
		}
		pointer = move;
		return result;
	}
	bool Free(void* objectPointer, size_t size)
	{
		if (pointer == startPointer)
			return false;
		if (objectPointer != pointer)
			return false;
		
		pointer -= size;
		return true;
	}
	void Clear()
	{
		pointer = startPointer;
	}

private:
	char* startPointer = nullptr;
	char* endPointer = nullptr;
	char* pointer = nullptr;
	MemoryPool::Memory* memory = nullptr;
};