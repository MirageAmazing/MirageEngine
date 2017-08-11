#include <iostream>
#include <new>
#include <Core\Math\TQuaternion.h>
#include <Core\Math\TVector3.h>
#include <Core\Allocator\MemoryPool.h>
#include <Core\Allocator\Allocator.h>
using namespace std;
using Vector = TVector3;

class Alloctor
{
public:
	static Alloctor* Instance() 
	{
		if (mInstance == nullptr)
			mInstance = new Alloctor(1024);
		return mInstance;
	}
	void* alloctor(size_t size)
	{
		auto pResult = mPointer;
		mPointer += size;
		return pResult;
	}

private:
	Alloctor(size_t size)
	{
		mMemory = (char*)malloc(size);
		mPointer = mMemory;
	}
	~Alloctor()
	{
		free(mMemory);
	}

	
private:
	char* mPointer;
	char* mMemory;
	static Alloctor* mInstance;
};
Alloctor* Alloctor::mInstance = nullptr;

template<class T>
class MyAlloctor
{
public:
	MyAlloctor(){}

	T* allocte(int count)
	{
		auto pArray = (T*)Alloctor::Instance()->alloctor(count*sizeof(T));
		return pArray;
	}

	template<class... _Types>
	void construct(T* pObj, _Types&&... _Args) 
	{
		new(pObj) T(forward<_Types>(_Args)...);
	}
};

class MyClass
{
public:
	MyClass()
	{
		x = 0;
		y = 0;
	}
	MyClass(int ix, int iy)
	{
		x = ix;
		y = iy;
	}
	MyClass(int ix, int iy, float iz)
	{
		x = ix;
		y = iy;
		z = iz;
	}

	int x = 0;
	int y = 0;
	float z = 0;
};


class FreeList
{
private:
	struct FreeListNode
	{
		FreeListNode(size_t size)
		{
			memory = malloc(size);
		}
		~FreeListNode()
		{
			free(memory);
		}
		size_t sizeofMemory;
		void* memory;
		FreeListNode* previous = nullptr;
		FreeListNode* next = nullptr;
	};
public:
	FreeList() {}
	~FreeList() {}

	FreeListNode* Allocate(size_t size)
	{
		FreeListNode* node = new FreeListNode(size);
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
		return node;
	}
	bool ReAllocate(FreeListNode* node)
	{
		auto pointer = freeListNode;
		if (pointer == nullptr)
			return false;

		do
		{
			if (pointer == node)
			{
				auto preNode = pointer->previous;
				auto nextNode = pointer->next;
				if(preNode != nullptr)preNode->next = nextNode;
				if(nextNode != nullptr)nextNode->previous = preNode;
				delete node;
				return true;
			}
			pointer = pointer->previous;
		} while (pointer != nullptr);

		return false;
	}

private:
	FreeListNode* freeListNode = nullptr;
};

int main(int argsCount, char** args)
{
	MyAlloctor<MyClass> aint;

	MyClass* p1 = aint.allocte(2); 
	aint.construct(&p1[0], 23, 45);
	aint.construct(&p1[1], 65, 45);
	
	cout << p1[0].x << "  " << p1[1].x << endl;

	MyClass* p2 = aint.allocte(2);
	aint.construct(&p2[0], 77, 45);
	aint.construct(&p2[1], 98, 45);
	cout << p2[0].x << "  " << p2[1].x << endl;

	auto memoryPool = MemoryPool::Get();

	auto memoryA = memoryPool->Allocate(sizeof(MyClass));
	auto memoryB = memoryPool->Allocate(sizeof(MyClass));
	auto memoryC = memoryPool->Allocate(sizeof(MyClass));
	cout << memoryPool->GetSize() << endl;
	memoryPool->ReAllocate(memoryA);
	cout << memoryPool->GetSize() << endl;
	memoryPool->ReAllocate(memoryB);
	cout << memoryPool->GetSize() << endl;
	memoryPool->ReAllocate(memoryC);
	cout << memoryPool->GetSize() << endl;

	auto stackAlloctor = StackAllocator::Get(32);

	stackAlloctor->Allocate(1);
	stackAlloctor->Allocate(15);
	stackAlloctor->Allocate(15);
	auto p = stackAlloctor->Allocate(1);
	cout << (int)p << endl;

	StackAllocator::Delete(stackAlloctor);

	auto poolAllocator = PoolAllocator<MyClass>::Get(4);
	auto obj1 = poolAllocator->Allocte(12, 23, 56);
	auto obj2 = poolAllocator->Allocte(12, 23, 78);
	auto obj3 = poolAllocator->Allocte(12, 23, 78);
	auto obj4 = poolAllocator->Allocte(12, 23, 78);
	auto obj5 = poolAllocator->Allocte(12,23,78);
	PoolAllocator<MyClass>::Delete(poolAllocator);

	system("pause");
	return 0;
}