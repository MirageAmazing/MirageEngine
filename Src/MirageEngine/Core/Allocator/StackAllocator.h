#pragma once
#include "MemoryPool.h"
#include "AllocatorBase.h"
#include <memory>
#include <list>

class StackAllocator:public AllocatorBase<StackAllocator>
{
public:
	explicit StackAllocator(size_t size);
	StackAllocator(StackAllocator&& alloctor);
	~StackAllocator();

	StackAllocator() = delete;
	StackAllocator& operator = (const StackAllocator&) = delete;

	void* Allocate(size_t size);
	bool Free(void* objectPointer, size_t size);
	void Clear();

private:
	char* startPointer = nullptr;
	char* endPointer = nullptr;
	char* pointer = nullptr;
	MemoryPool::Memory* memory = nullptr;
};