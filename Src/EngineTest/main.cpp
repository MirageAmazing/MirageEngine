#include <string>

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

using namespace std;
using namespace MirageMath;
using namespace Mirage::Render;

void TestMain();

int main(int argc, char* argv[])
{
	TestMain();

#if defined(MIRAGE_PLATFORM_WINDOWS)
#else
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

	bool isRun = true;
	SDL_Window *window = 0;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Mirage", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

#if defined(MIRAGE_PLATFORM_WINDOWS)
	auto render = BaseRender::GetRender(RenderType::DirectX11, 800, 600, window);
#else
	auto render = BaseRender::GetRender(RenderType::OpenGL40, 800, 600, window);
#endif

	float colorVar = 0;

	while (isRun)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EventType::SDL_QUIT:
				isRun = false;
				break;
			}
		}
		render->SetClearColor(0, colorVar, 0);
		render->Frame();

		if (colorVar > 1) colorVar = 0;
		else colorVar += 0.001f;
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void TestMain()
{
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

	int x = 0;
	x++;
}