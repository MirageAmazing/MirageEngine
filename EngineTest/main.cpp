#include <iostream>
#include <Core\Math\TQuaternion.h>
#include <Core\Math\TVector3.h>
using namespace std;

void main()
{
	TQuaternion a(1, 2, 3, 1);
	TQuaternion b(1, 2, 3, 1);

	auto c = a*b;

	TVector3 va(1, 2, 3);
	TVector3 vb(1, 2, 3);

	auto vc = TVector3::Cross(va, vb);

	system("pause");
}