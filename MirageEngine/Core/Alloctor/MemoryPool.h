#pragma once
#include <new>

class MemoryPool
{
public:
	struct Memory
	{
		size_t sizeofMemory;
		void* memory;
	};
private:
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
	static MemoryPool& Get()
	{
		if (Instance == nullptr)
			Instance = new MemoryPool();
		return *Instance;
	}
	static bool Free()
	{
		if (Instance != nullptr)
		{
			delete Instance;
			Instance = nullptr;
		}
	}
	static MemoryPool* Instance;

private:
	MemoryPool() {}	
	~MemoryPool()
	{
		if (wholeSize != 0)
		{
			// expection!
		}
	}

public:
	MemoryPool(const MemoryPool&) = delete;
	MemoryPool& operator=(const MemoryPool&) = delete;

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
	bool ReAllocate(Memory* node)
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

	size_t GetSize()
	{
		return wholeSize;
	}
private:
	MemoryNode* freeListNode = nullptr;
	size_t wholeSize = 0;
};

MemoryPool* MemoryPool::Instance = nullptr;