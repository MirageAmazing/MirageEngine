#include "MirageEngine.h"
#include "RenderOGL4.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include "SDL2/SDL_opengl.h"

using namespace std;

namespace Mirage {
	namespace Render {

		RenderOGL4::RenderOGL4(int iScreenWidth, int iScreenHeight, void* pWindowHandle)
			:Render(iScreenWidth, iScreenHeight, pWindowHandle){				
			mWindow = (SDL_Window*)pWindowHandle;

			auto context = SDL_GL_CreateContext(mWindow);

			if (context == nullptr)
			{
				cout << "OpenGL40 initialization failed!" << endl;
				return;
			}
			else
			{
				cout << "OpenGL40 initialization succeeded!" << endl;
				glewInit();
				glEnable(GL_DEPTH_TEST);
				glViewport(0, 0, iScreenWidth, iScreenHeight);
			}

			mCamera = std::unique_ptr<Camera>(new Camera(Vector3f(260, 0, 0), Vector3f(0, 0, 0), Vector3f(0, 1, 0), iScreenWidth, iScreenHeight));
			mCamera->SetProjPerspertiveType(eCameraProjPerspertiveType::PerspertiveV2);
			PrepareResource();
		}

		RenderOGL4::~RenderOGL4()
		{

		}

		void RenderOGL4::OnSetClearColor()
		{

		}
		GLuint RenderOGL4::LoadShaders(const char* vs, const char* ps)
		{
			GLuint vsID = glCreateShader(GL_VERTEX_SHADER);
			GLuint psID = glCreateShader(GL_FRAGMENT_SHADER);

			// Load vscode from disk
			string vsCode;
			ifstream vsStream(vs, ios::in);
			if (vsStream.is_open()) {
				stringstream sstr;
				sstr << vsStream.rdbuf();
				vsCode = sstr.str();
				vsStream.close();
			}
			else {
				printf("vs shader %s have some wrong!", vs);
				return 0;
			}

			// Load pscode from disk
			string psCode;
			ifstream psStream(ps, ios::in);
			if (psStream.is_open()) {
				stringstream sstr;
				sstr << psStream.rdbuf();
				psCode = sstr.str();
				psStream.close();
			}
			else {
				printf("ps shader %s have some wrong!", ps);
				return 0;
			}

			// Compile vs
			GLint r = GL_FALSE;
			int InfoLogLength;
			const char* vsPointer = vsCode.c_str();
			glShaderSource(vsID, 1, &vsPointer, nullptr);
			glCompileShader(vsID);
			// Check vs
			glGetShaderiv(vsID, GL_COMPILE_STATUS, &r);
			glGetShaderiv(vsID, GL_INFO_LOG_LENGTH, &InfoLogLength);
			if (InfoLogLength > 0) {
				string vsErrorMsg{ "" };
				vsErrorMsg.resize(InfoLogLength + 1);
				glGetShaderInfoLog(vsID, InfoLogLength, nullptr, &vsErrorMsg[0]);
				printf("%s\n", &vsErrorMsg[0]);
			}

			// Compile ps
			const char* psPointer = psCode.c_str();
			glShaderSource(psID, 1, &psPointer, nullptr);
			glCompileShader(psID);
			// Check ps
			glGetShaderiv(psID, GL_COMPILE_STATUS, &r);
			glGetShaderiv(psID, GL_INFO_LOG_LENGTH, &InfoLogLength);
			if (InfoLogLength > 0) {
				string psErrorMsg{ "" };
				psErrorMsg.resize(InfoLogLength + 1);
				glGetShaderInfoLog(psID, InfoLogLength, nullptr, &psErrorMsg[0]);
				printf("%s\n", &psErrorMsg[0]);
			}

			// Link the program
			GLuint programID = glCreateProgram();
			glAttachShader(programID, vsID);
			glAttachShader(programID, psID);
			glLinkProgram(programID);
			// Check the program
			glGetProgramiv(programID, GL_LINK_STATUS, &r);
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
			if (InfoLogLength > 0) {
				string programErrorMsg{ "" };
				programErrorMsg.resize(InfoLogLength + 1);
				glGetShaderInfoLog(psID, InfoLogLength, nullptr, &programErrorMsg[0]);
				printf("%s\n", &programErrorMsg[0]);
			}

			glDetachShader(programID, vsID);
			glDetachShader(programID, psID);
			glDeleteShader(vsID);
			glDeleteShader(psID);

			return programID;
		}
		
		const float tem = 2.5;
		const GLfloat positions[] =
		{
			tem, tem, -tem,
			tem, -tem, -tem,
			-tem, -tem, -tem,
			-tem, tem, -tem,
			-tem, tem, tem,
			-tem, -tem, tem,
			tem, -tem, tem,
			tem, tem, tem
		};
		const GLfloat colors[] =
		{
			1,0,0,
			1,1,0,
			1,0,1,
			1,1,0,
			1,0,1,
			1,1,0,
			1,0,1,
			0,1,1
		};
		const GLushort indices[] =
		{
			0,1,2,
			0,2,3,
			0,3,7,
			3,4,7,
			7,5,4,
			7,6,5,
			6,1,2,
			6,2,5,
			3,2,5,
			4,3,5,
			0,7,6,
			0,6,1
		};
		void RenderOGL4::PrepareResource()
		{
			glGenBuffers(1, &mVertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
			glGenBuffers(1, &mColorBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, mColorBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
			glGenBuffers(1, &mIndexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, mIndexBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			mProgramID = LoadShaders("../../MirageEngine/Resource/Shader/vs.glsl", "../../MirageEngine/Resource/Shader/ps.glsl");
			mMatrixID = glGetUniformLocation(mProgramID, "MVP");
			glUseProgram(mProgramID);

		}

		float anglea = 0;
		void RenderOGL4::Frame()
		{
			glClearColor(mClearColor[0], mClearColor[1], mClearColor[2], 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			mCamera->SetViewLocation(Vector3f(10.0*cos(DegreeToRadians(anglea)), 0, 10.0*sin(DegreeToRadians(anglea))));
			mCamera->SetViewTarget(Vector3f(0, 0, 0));
			anglea += 0.04;
			//mTransform.AddTranslation(5,0,0);
			auto worldMat = mTransform.GetTransformMatrix().Transpose();
			auto viewMat = mCamera->GetViewMatrix().Transpose();
			auto projMat = mCamera->GetProjectionMatrix().Transpose();
			auto mvp = projMat*viewMat*worldMat;

			glUseProgram(mProgramID);

			glUniformMatrix4fv(mMatrixID, 1, GL_FALSE, &mvp[0][0]);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, mColorBufferID);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);

			glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLushort), GL_UNSIGNED_SHORT, (void*)0);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);

			/*glBegin(GL_LINE_LOOP);
			glVertex2f(mVertex, mVertex);
			glVertex2f(0.75, 0.25);
			glVertex2f(0.75, 0.75);
			glVertex2f(0.25, 0.75);
			glEnd();
*/
			SDL_GL_SwapWindow(mWindow);
		}
	}
}
