#include "DoubleEndedStackAllocator.h"

DoubleEndedStackAllocator::DoubleEndedStackAllocator(size_t size)
{
    memory = MemoryPool::Get()->Allocate(size);
    startPointer = static_cast<char*>(memory->memory);
    endPointer = startPointer + size;
    pointerFromStart = startPointer;
    pointerFromEnd = endPointer;
}

void* DoubleEndedStackAllocator::AllocFromStart(size_t size)
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

void* DoubleEndedStackAllocator::AllocFromEnd(size_t size)
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

bool DoubleEndedStackAllocator::FreeBaseStart(void* pointer, size_t size)
{
    if (pointer == startPointer)
        return false;
    if (pointerFromStart != pointer)
        return false;

    pointerFromStart -= size;
    return true;
}

bool DoubleEndedStackAllocator::FreeBaseEnd(void* pointer, size_t size)
{
    if (pointer == endPointer)
        return false;
    if (pointerFromEnd != pointer)
        return false;

    pointerFromEnd += size;
    return true;
}

void DoubleEndedStackAllocator::Clear()
{
    if (pointerFromStart != startPointer || pointerFromEnd != endPointer)
    {
        // Exception
    }
    pointerFromStart = startPointer;
    pointerFromEnd = endPointer;
}