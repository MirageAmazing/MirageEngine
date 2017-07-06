#include <iostream>
#include <new>
#include <Core\Math\TQuaternion.h>
#include <Core\Math\TVector3.h>
using namespace std;

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

class Color
{
public:
	Color(float InR, float InG, float InB)
	{
		r = InR;
		g = InG;
		b = InB;
	}

	float r, g, b;
};
Color operator "" _C(const char* col, size_t n) 
{
	const char* p = col;
	const char* end = col + n;
	const char* r, *g, *b;
	r = g = b = nullptr;
	for (; p != end;++p)
	{
		if (*p == 'r') r = p;
		else if (*p == 'g') g = p;
		else if (*p == 'b') b= p;
	}
	if ((r == nullptr) || (g == nullptr) || (b == nullptr))
		throw;
	else
		return Color(atoi(r+1), atoi(g+1), atoi(b+1));
}
std::ostream & operator<<(ostream& out, const Color& col)
{
	return out << "r: " << (int)col.r
		<< ",g: " << (int)col.g
		<< ",b: " << (int)col.b << endl;
}

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
	
	cout << "r255g234b123"_C << endl;

	system("pause");
	return 0;
}