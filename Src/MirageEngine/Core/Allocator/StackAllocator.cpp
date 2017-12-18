#include "StackAllocator.h"

StackAllocator::StackAllocator(size_t size)
{
    memory = MemoryPool::Get()->Allocate(size);
    startPointer = static_cast<char*>(memory->memory);
    endPointer = startPointer+size;
    pointer = startPointer;
}
StackAllocator::StackAllocator(StackAllocator&& alloctor)
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
StackAllocator::~StackAllocator()
{
    if (pointer != startPointer)
    {
        //TODO:Exception
    }
    MemoryPool::Get()->ReAllocate(memory);
}

void* StackAllocator::Allocate(size_t size)
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
bool StackAllocator::Free(void* objectPointer, size_t size)
{
    if (pointer == startPointer)
        return false;
    if (objectPointer != pointer)
        return false;
    
    pointer -= size;
    return true;
}
void StackAllocator::Clear()
{
    pointer = startPointer;
}