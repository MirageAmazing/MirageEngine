#include <string>
#include <type_traits>

#include "SDL2/SDL.h"
#include "SDL2/SDL_main.h"

#include "../MirageEngine/MirageEngine.h"
#include "../MirageEngine/Render/Render/Render.h"
#include "../MirageEngine/Core/Math/Vector2.h"
#include "../MirageEngine/Core/Math/Vector3.h"
#include "../MirageEngine/Core/Math/Matrix.h"
#include "../MirageEngine/Core/Math/Quaternion.h"
#include "../MirageEngine/Core/Math/VersionNumber.h"
#include "../MirageEngine/Resource/ResourceSystem.h"
#include "../MirageEngine/Core/HAL/MMalloc.h"
#include "../MirageEngine/Core/HAL/IOBase.h"

#include "../MirageEngine/Core/Windows/WindowsApplication.h"
#include "../MirageEngine/Core/Linux/LinuxApplication.h"

using namespace std;
using namespace Mirage::Math;
using namespace Mirage::Application;

void TestMain();
Matrix4x4f LookAt(const Vector3f& eye, const Vector3f& target, const Vector3f& up)
{
	Vector3f forward((target - eye).GetNormal());
	Vector3f right((Vector3f::Cross(forward, up).GetNormal()));
	
	Matrix4x4f result;

	result[0] [0]= right.x;
	result[1][0] = right.y;
	result[2][0] = right.z;
	result[3][0] =0;

	result[0][1] = up.x;
	result[1][1] = up.y;
	result[2][1] = up.z;
	result[3][1] = 0;

	result[0][2] = forward.x;
	result[1][2] = forward.y;
	result[2][2] = forward.z;
	result[3][2] = 0;

	result[0][3] = eye.x;
	result[1][3] = eye.y;
	result[2][3] = eye.z;
	result[3][3] = 1.0f;

	return result;
}
int main(int argc, char* argv[])
{
	TestMain();

#if defined(MIRAGE_PLATFORM_WINDOWS)
	Mirage::Application::Application* pApp = new WindowsApplication();
#else defined(MIRAGE_PLATFORM_LINUX)
	Mirage::Application::Application* pApp = new LinuxApplication();
#endif

	while (!pApp->IsQuit()){
		pApp->Tick();
	}

	delete pApp;

	return 0;
}

void TestMain()
{
	auto n = Vector4f(1, 2, 3,1);
	auto mat = LookAt(Vector3f(200, 0, 0), Vector3f(10,10,0), Vector3f(0,1,0));
	auto mate1 = mat[0][2];
	auto matT = mat.Transpose();
	auto tm = Matrix4x4f::Translate(10, 20, 12);
	auto tm1 = Matrix4x4f::Translate(10,20,12);
	auto r = (tm*tm1)*n;
	Vector2f vecA(12, 90);
	Vector2f vecB(65, 45);

	auto vecC = 2.0f*vecA + 300.0f / vecB;
	auto result = Vector2f::Dot(vecA, vecB);

	Vector3f vecAA(1, 2, 3);
	Vector3f vecBB(2, 24, 13);
	auto vecCC = vecAA + vecBB + Vector3f::Left;

	Matrix4x4f mA = Matrix4x4f::IndentityMatrix();
	auto mB = mA*32.0f;
	mB = 23 * mB;

	Matrix3x3f m3A = Matrix3x3f::IndentityMatrix();
	m3A[0][1] = 23;
	m3A[1][0] = 3;

	auto m3A_Invered = m3A.Inverse();
	auto m3A_Result = m3A*m3A_Invered;

	auto size = sizeof(MEUID);

	VersionNumber vn(1, 2, 4);
	VersionNumber vn1 = "3"_v;
	VersionNumber vn2("2.");
	VersionNumber vn3("2.1");
	VersionNumber vn4("2.1.");
	VersionNumber vn5("2.1.1");
	VersionNumber vn6 = "2.1.2"_v;

	if (vn6 > vn5)
		vn = vn1;
	if (vn2 > vn3)
		vn = vn1;
	if ("1.1.2"_v > "1.0.9"_v)
		vn = vn1;

	auto rs = Mirage::Resource::ResouceSystem::GetInstance();
	
	auto ispod = std::is_pod<Vector3f>::value;

	auto r1 = DegreeToRadians(180);
	auto r2 = DegreeToRadians(60);
	auto r3 = DegreeToRadians(45);

	Quaternionf quat(3.14, 0.6, 0.9);
	auto eular = quat.Eular();

	char buff[1000];
	size_t datasize;
	if (FileIOSystem::Get().LoadFile("../../MirageEngine/Resource/Shader/basic.HLSL", buff, 1000, datasize)) {
		cout << "Succeed" << endl;
	}
	else {
		cout << "Failed"<<endl;
	}

	int x = 0;
	x++;
}