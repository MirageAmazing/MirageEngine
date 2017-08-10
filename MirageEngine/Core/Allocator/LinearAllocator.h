#pragma once

#include "MemoryPool.h"
#include "AllocatorBase.h"
#include <memory>

class LinearAllocator:public AllocatorBase<LinearAllocator>
{
public:
	explicit LinearAllocator(size_t size)
	{
		memory = MemoryPool::Get()->Allocate(size);
		startPointer = static_cast<char*>(memory->memory);
		endPointer = startPointer + size;
		pointer = startPointer;
	}
	LinearAllocator(LinearAllocator&& alloctor)
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
	~LinearAllocator()
	{
		if (pointer != startPointer)
		{
			//TODO:Exception
		}
		MemoryPool::Get()->ReAllocate(memory);
	}

	LinearAllocator() = delete;
	LinearAllocator& operator = (const LinearAllocator&) = delete;

	void* Allocate(size_t size)
	{
		auto result = pointer;
		auto move = pointer + size;
		if (move > endPointer)
		{
			//TODO:Exception
			return nullptr;
		}
		pointer = move;
		return result;
	}

	/** Dangerous Action. */
	void Reset()
	{
		pointer = startPointer;
	}

private:
	char* startPointer = nullptr;
	char* endPointer = nullptr;
	char* pointer = nullptr;
	MemoryPool::Memory* memory = nullptr;
};