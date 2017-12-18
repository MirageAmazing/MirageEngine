#pragma once
#include <new>
#include <stdlib.h>

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
	static MemoryPool* Get();
	static bool Free();	
private:
	MemoryPool();
	~MemoryPool();	
public:
	MemoryPool(const MemoryPool&) = delete;
	MemoryPool& operator=(const MemoryPool&) = delete;

	Memory* Allocate(size_t size);
	bool ReAllocate(Memory* node);

	size_t GetSize();
private:
	MemoryNode* freeListNode = nullptr;
	size_t wholeSize = 0;
	static MemoryPool* Instance;
};