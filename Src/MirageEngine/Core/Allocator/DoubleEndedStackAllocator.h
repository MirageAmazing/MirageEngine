#pragma once
#include "MemoryPool.h"
#include "AllocatorBase.h"
#include <memory>

class DoubleEndedStackAllocator:public AllocatorBase<DoubleEndedStackAllocator>
{
public:
	explicit DoubleEndedStackAllocator(size_t size);

	DoubleEndedStackAllocator() = delete;
	DoubleEndedStackAllocator& operator = (const DoubleEndedStackAllocator&) = delete;

	void* AllocFromStart(size_t size);
	void* AllocFromEnd(size_t size);
	bool FreeBaseStart(void* pointer, size_t size);
	bool FreeBaseEnd(void* pointer, size_t size);
	void Clear();

private:
	char* startPointer = nullptr;
	char* endPointer = nullptr;
	char* pointerFromStart = nullptr;
	char* pointerFromEnd = nullptr;
	MemoryPool::Memory* memory = nullptr;
};