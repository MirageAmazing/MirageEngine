#include <string>
#include <type_traits>

#include "SDL2/SDL.h"
#include "SDL2/SDL_main.h"

#include "../MirageEngine/MirageEngine.h"
#include "../MirageEngine/Render/BaseRender/BaseRender.h"
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
	Vector3f z((eye - target).Normalize());
	Vector3f x((Vector3f::Cross(z, up).Normalize()));
	Vector3f y(Vector3f::Cross(x, z));

	Matrix4x4f result;

	result[0] [0]= x.x;
	result[1][0] = x.y;
	result[2][0] = x.z;
	result[3][0] = -Vector3f::Dot(x, eye);

	result[0][1] = y.x;
	result[1][1] = y.y;
	result[2][1] = y.z;
	result[3][1] = -Vector3f::Dot(y, eye);

	result[0][2] = z.x;
	result[1][2] = z.y;
	result[2][2] = z.z;
	result[3][2] = -Vector3f::Dot(z, eye);

	result[0][3] = result[1][3] = result[2][3] = 0.0f;
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
	auto mat = LookAt(Vector3f(200, 0, 0), Vector3f(10,10,0), Vector3f(0,1,0));
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
	auto meshData = rs->CreateMeshRes();
	Mirage::Resource::Vertex v1, v2, v3;
	v1.position = Vector3f(0.0f, 0.0f, 0.0f);
	v2.position = Vector3f(10, 10, 10);
	v3.position = Vector3f(10, 10, 0);
	meshData->AddVertex(v1);
	meshData->AddVertex(v2);
	meshData->AddVertex(v3);

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