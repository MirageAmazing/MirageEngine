#pragma once

#include "MemoryPool.h"
#include <memory>

class LinearAlloctor
{
public:
	LinearAlloctor(int size)
	{
		memory = MemoryPool::Get().Allocate(size);
		startPointer = static_cast<char*>(memory->memory);
		endPointer = startPointer + size - 1;
		pointer = startPointer;
	}
	LinearAlloctor(LinearAlloctor&& alloctor)
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
	~LinearAlloctor()
	{
		if (pointer != startPointer)
		{
			//TODO:Exception
		}
		MemoryPool::Get().ReAllocate(memory);
	}

	LinearAlloctor() = delete;
	LinearAlloctor& operator = (const LinearAlloctor&) = delete;

	void* Allocate(size_t size)
	{
		auto result = pointer + size;
		if (result >= endPointer)
		{
			//TODO:Exception
			return nullptr;
		}
		pointer == result;
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