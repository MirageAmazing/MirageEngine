#pragma once
#include "MemoryPool.h"
#include "AllocatorBase.h"
#include <memory>

template<class T>
class PoolAllocator:public AllocatorBase<PoolAllocator<T>>
{
public:
	PoolAllocator(size_t count) 
	{
		memory = MemoryPool::Get()->Allocate(count*sizeof(T));
	}
	~PoolAllocator() 
	{
		MemoryPool::Get()->ReAllocate(memory);
	}
private:
	MemoryPool::Memory* memory = nullptr;
};