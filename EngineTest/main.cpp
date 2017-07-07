#include <iostream>
#include <new>
#include <Core\Math\TQuaternion.h>
#include <Core\Math\TVector3.h>
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

	int x = 0;
	int y = 0;
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

	system("pause");
	return 0;
}