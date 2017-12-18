#include "MemoryPool.h"

MemoryPool* MemoryPool::Get()
{
    if (Instance == nullptr)
        Instance = new MemoryPool();
    return Instance;
}
bool MemoryPool::Free()
{
    if (Instance != nullptr)
    {
        delete Instance;
        Instance = nullptr;
        return true;
    }
    return false;
}

MemoryPool* MemoryPool::Instance = nullptr;

MemoryPool::MemoryPool() 
{

}	

MemoryPool::~MemoryPool()
{
    if (wholeSize != 0)
    {
        // expection!
    }
}

MemoryPool::Memory* MemoryPool::Allocate(size_t size)
{
    MemoryNode* node = new MemoryNode(size);
    if (node == nullptr)
        return nullptr;
    if (freeListNode == nullptr)
    {
        freeListNode = node;
    }
    else
    {
        node->previous = freeListNode;
        freeListNode->next = node;
        freeListNode = node;
    }
    wholeSize += size;
    return &node->memory;
}

bool MemoryPool::ReAllocate(MemoryPool::Memory* node)
{
    auto pointer = freeListNode;
    if (pointer == nullptr)
        return false;

    do
    {
        if (pointer->memory.memory == node->memory)
        {
            auto preNode = pointer->previous;
            auto nextNode = pointer->next;
            if (preNode != nullptr)preNode->next = nextNode;
            if (nextNode != nullptr)nextNode->previous = preNode;
            wholeSize -= pointer->memory.sizeofMemory;
            delete pointer;
            return true;
        }
        pointer = pointer->previous;
    } while (pointer != nullptr);

    return false;
}

size_t MemoryPool::GetSize()
{
    return wholeSize;
}