#pragma once
#include "MemoryPool.h"
#include "AllocatorBase.h"
#include <memory>

class DoubleEndedStackAllocator:public AllocatorBase<DoubleEndedStackAllocator>
{
public:
	explicit DoubleEndedStackAllocator(size_t size)
	{
		memory = MemoryPool::Get()->Allocate(size);
		startPointer = static_cast<char*>(memory->memory);
		endPointer = startPointer + size;
		pointerFromStart = startPointer;
		pointerFromEnd = endPointer;
	}

	DoubleEndedStackAllocator() = delete;
	DoubleEndedStackAllocator& operator = (const DoubleEndedStackAllocator&) = delete;

	void* AllocFromStart(size_t size)
	{
		auto result = pointerFromStart;
		auto move = pointerFromStart + size;
		if (move > pointerFromEnd)
		{
			//TODO:Exception
			return nullptr;
		}
		pointerFromStart = move;
		return result;
	}
	void* AllocFromEnd(size_t size)
	{
		auto result = pointerFromEnd - size;
		if (result < pointerFromStart)
		{
			//TODO:Exception
			return nullptr;
		}
		pointerFromEnd = result;
		return result;
	}
	bool FreeBaseStart(void* pointer, size_t size)
	{
		if (pointer == startPointer)
			return false;
		if (pointerFromStart != pointer)
			return false;

		pointerFromStart -= size;
		return true;
	}
	bool FreeBaseEnd(void* pointer, size_t size)
	{
		if (pointer == endPointer)
			return false;
		if (pointerFromEnd != pointer)
			return false;

		pointerFromEnd += size;
		return true;
	}
	void Clear()
	{
		if (pointerFromStart != startPointer || pointerFromEnd != endPointer)
		{
			// Exception
		}
		pointerFromStart = startPointer;
		pointerFromEnd = endPointer;
	}

private:
	char* startPointer = nullptr;
	char* endPointer = nullptr;
	char* pointerFromStart = nullptr;
	char* pointerFromEnd = nullptr;
	MemoryPool::Memory* memory = nullptr;
};