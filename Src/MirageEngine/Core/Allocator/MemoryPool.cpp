#include "../HAL/MMalloc.h"
#include "MemoryPool.h"

namespace Mirage {
	namespace Core {
		MemoryPool* MemoryPool::Get()
		{
			if (Instance == nullptr)
				Instance = mmalloc.New<MemoryPool>();
			return Instance;
		}
		bool MemoryPool::Free()
		{
			if (Instance != nullptr)
			{
				mmalloc.Delete<MemoryPool>(Instance);
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
			MemoryNode* node = mmalloc.New<MemoryNode>(size);
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
					mmalloc.Delete<MemoryNode>(pointer);
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
	}
}