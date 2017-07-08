#pragma once
#include "MemoryPool.h"
#include <memory>

class StackAlloctor
{
public:
	StackAlloctor(int size)
	{
		memory = MemoryPool::Get().Allocate(size);
		startPointer = static_cast<char*>(memory->memory);
		endPointer = startPointer+size-1;
		pointer = startPointer;
	}
	StackAlloctor(StackAlloctor&& alloctor)
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
	~StackAlloctor()
	{
		if (pointer != startPointer)
		{
			//TODO:Exception
		}
		MemoryPool::Get().ReAllocate(memory);
	}

	StackAlloctor() = delete;
	StackAlloctor& operator = (const StackAlloctor&) = delete;

	void* Allocate(size_t size)
	{
		auto result = pointer;
		if (result == endPointer)
		{
			//TODO:Exception
			return nullptr;
		}
		pointer += size;
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
	/** Dangerous Action. */
	void FreeAll()
	{
		pointer = startPointer;
	}

private:
	char* startPointer = nullptr;
	char* endPointer = nullptr;
	char* pointer = nullptr;
	MemoryPool::Memory* memory = nullptr;
};