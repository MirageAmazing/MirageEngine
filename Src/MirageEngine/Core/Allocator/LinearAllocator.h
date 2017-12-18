#pragma once

#include "MemoryPool.h"
#include "AllocatorBase.h"
#include <memory>

class LinearAllocator:public AllocatorBase<LinearAllocator>
{
public:
	explicit LinearAllocator(size_t size);
	LinearAllocator(LinearAllocator&& alloctor);
	~LinearAllocator();

	LinearAllocator() = delete;
	LinearAllocator& operator = (const LinearAllocator&) = delete;

	void* Allocate(size_t size);
	/** Dangerous Action. */
	void Reset();

private:
	char* startPointer = nullptr;
	char* endPointer = nullptr;
	char* pointer = nullptr;
	MemoryPool::Memory* memory = nullptr;
};