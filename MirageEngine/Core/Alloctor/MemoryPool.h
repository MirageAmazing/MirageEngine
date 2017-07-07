#pragma once
#include <new>

class MemoryPool
{
private:
	struct Memory
	{
		size_t sizeofMemory;
		void* memory;
	};
	struct MemoryNode
	{
		MemoryNode(size_t size)
		{
			memory.memory = malloc(size);
			memory.sizeofMemory = size;
		}
		~MemoryNode()
		{
			free(memory.memory);
		}
		Memory memory;
		MemoryNode* previous = nullptr;
		MemoryNode* next = nullptr;
	};
public:
	MemoryPool() {}
	~MemoryPool()
	{
		if (wholeSize != 0)
		{
			// expection!
		}
	}

	Memory* Allocate(size_t size)
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
	bool ReAllocate(Memory node)
	{
		auto pointer = freeListNode;
		if (pointer == nullptr)
			return false;

		do
		{
			if (pointer->memory.memory == node.memory)
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

private:
	MemoryNode* freeListNode = nullptr;
	size_t wholeSize = 0;
};