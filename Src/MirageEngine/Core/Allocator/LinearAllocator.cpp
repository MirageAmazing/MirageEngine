#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(size_t size)
{
    memory = MemoryPool::Get()->Allocate(size);
    startPointer = static_cast<char*>(memory->memory);
    endPointer = startPointer + size;
    pointer = startPointer;
}
LinearAllocator::LinearAllocator(LinearAllocator&& alloctor)
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
LinearAllocator::~LinearAllocator()
{
    if (pointer != startPointer)
    {
        //TODO:Exception
    }
    MemoryPool::Get()->ReAllocate(memory);
}


void* LinearAllocator::Allocate(size_t size)
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
void LinearAllocator::Reset()
{
    pointer = startPointer;
}