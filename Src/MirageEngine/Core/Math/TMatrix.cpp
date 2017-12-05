#include "TMatrix.h"
#include "TVector3.h"
#include "TMath.h"
#include <string.h>
#include <cmath>

TMatrix::TMatrix()
{
	memset(data, 0, sizeof(int) * 16);
}

TMatrix::TMatrix(TVector3& InX, TVector3& InY, TVector3& InZ, TVector3& InW)
{
	data[0][0] = InX.x; data[0][1] = InX.y; data[0][2] = InX.z; data[0][3] = 0;
	data[1][0] = InY.x; data[1][1] = InY.y; data[1][2] = InY.z; data[1][3] = 0;
	data[2][0] = InZ.x; data[2][1] = InZ.y; data[2][2] = InZ.z; data[2][3] = 0;
	data[3][0] = InW.x; data[3][1] = InW.y; data[3][2] = InW.z; data[3][3] = 1;
}

TMatrix::TMatrix(TVector3&& InX, TVector3&& InY, TVector3&& InZ, TVector3&& InW)
{
	data[0][0] = InX.x; data[0][1] = InX.y; data[0][2] = InX.z; data[0][3] = 0;
	data[1][0] = InY.x; data[1][1] = InY.y; data[1][2] = InY.z; data[1][3] = 0;
	data[2][0] = InZ.x; data[2][1] = InZ.y; data[2][2] = InZ.z; data[2][3] = 0;
	data[3][0] = InW.x; data[3][1] = InW.y; data[3][2] = InW.z; data[3][3] = 1;
}

TMatrix::TMatrix(const TMatrix& In)
{
	for (int i=0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			data[i][j] = In.data[i][j];
		}
	}
}

TMatrix TMatrix::operator+(const TMatrix& InM) const
{
	TMatrix matrix;
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			matrix.data[i][j] = data[i][j] + InM.data[i][j];
		}
	}
	return matrix;
}

TMatrix TMatrix::operator-(const TMatrix& InM) const
{
	TMatrix matrix;
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			matrix.data[i][j] = data[i][j] - InM.data[i][j];
		}
	}
	return matrix;
}

TMatrix TMatrix::operator*(const TMatrix& InM) const
{
	TMatrix matrix;
	for (int i = 0;i < 4;i++)
	{
		for (int k = 0;k < 4;k++)
		{
			for (int j = 0;j < 4;j++)
			{
				matrix.data[i][k] += data[i][j] * InM.data[j][k];
			}
		}
	}
	return matrix;
}

TMatrix TMatrix::operator*(double In) const
{
	TMatrix matrix;
	for (int i = 0;i < 4;i++)
	{	
		for (int j = 0;j < 4;j++)
		{
			matrix.data[i][j] = data[i][j] * In;
		}
	}
	return matrix;
}

void TMatrix::operator = (const TMatrix& In) 
{
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			data[i][j] = In.data[i][j];
		}
	}
}

double* const TMatrix::operator[](const int In)
{
	return data[In];
}

TMatrix TMatrix::Inverse()
{
	TMatrix matrix;
	const double s0 = (double)(data[0][0]); const double s1 = (double)(data[0][1]); const double s2 = (double)(data[0][2]); const double s3 = (double)(data[0][3]);
	const double s4 = (double)(data[1][0]); const double s5 = (double)(data[1][1]); const double s6 = (double)(data[1][2]); const double s7 = (double)(data[1][3]);
	const double s8 = (double)(data[2][0]); const double s9 = (double)(data[2][1]); const double s10 = (double)(data[2][2]); const double s11 = (double)(data[2][3]);
	const double s12 = (double)(data[3][0]); const double s13 = (double)(data[3][1]); const double s14 = (double)(data[3][2]); const double s15 = (double)(data[3][3]);

	matrix.data[0][0] = s5 * s10 * s15 - s5 * s11 * s14 - s9 * s6 * s15 + s9 * s7 * s14 + s13 * s6 * s11 - s13 * s7 * s10;
	matrix.data[0][1] = -s1 * s10 * s15 + s1 * s11 * s14 + s9 * s2 * s15 - s9 * s3 * s14 - s13 * s2 * s11 + s13 * s3 * s10;
	matrix.data[0][2] = s1 * s6  * s15 - s1 * s7  * s14 - s5 * s2 * s15 + s5 * s3 * s14 + s13 * s2 * s7 - s13 * s3 * s6;
	matrix.data[0][3] = -s1 * s6  * s11 + s1 * s7  * s10 + s5 * s2 * s11 - s5 * s3 * s10 - s9  * s2 * s7 + s9  * s3 * s6;
	matrix.data[1][0] = -s4 * s10 * s15 + s4 * s11 * s14 + s8 * s6 * s15 - s8 * s7 * s14 - s12 * s6 * s11 + s12 * s7 * s10;
	matrix.data[1][1] = s0 * s10 * s15 - s0 * s11 * s14 - s8 * s2 * s15 + s8 * s3 * s14 + s12 * s2 * s11 - s12 * s3 * s10;
	matrix.data[1][2] = -s0 * s6  * s15 + s0 * s7  * s14 + s4 * s2 * s15 - s4 * s3 * s14 - s12 * s2 * s7 + s12 * s3 * s6;
	matrix.data[1][3] = s0 * s6  * s11 - s0 * s7  * s10 - s4 * s2 * s11 + s4 * s3 * s10 + s8  * s2 * s7 - s8  * s3 * s6;
	matrix.data[2][0] = s4 * s9  * s15 - s4 * s11 * s13 - s8 * s5 * s15 + s8 * s7 * s13 + s12 * s5 * s11 - s12 * s7 * s9;
	matrix.data[2][1] = -s0 * s9  * s15 + s0 * s11 * s13 + s8 * s1 * s15 - s8 * s3 * s13 - s12 * s1 * s11 + s12 * s3 * s9;
	matrix.data[2][2] = s0 * s5  * s15 - s0 * s7  * s13 - s4 * s1 * s15 + s4 * s3 * s13 + s12 * s1 * s7 - s12 * s3 * s5;
	matrix.data[2][3] = -s0 * s5  * s11 + s0 * s7  * s9 + s4 * s1 * s11 - s4 * s3 * s9 - s8  * s1 * s7 + s8  * s3 * s5;
	matrix.data[3][0] = -s4 * s9  * s14 + s4 * s10 * s13 + s8 * s5 * s14 - s8 * s6 * s13 - s12 * s5 * s10 + s12 * s6 * s9;
	matrix.data[3][1] = s0 * s9  * s14 - s0 * s10 * s13 - s8 * s1 * s14 + s8 * s2 * s13 + s12 * s1 * s10 - s12 * s2 * s9;
	matrix.data[3][2] = -s0 * s5  * s14 + s0 * s6  * s13 + s4 * s1 * s14 - s4 * s2 * s13 - s12 * s1 * s6 + s12 * s2 * s5;
	matrix.data[3][2] = s0 * s5  * s10 - s0 * s6  * s9 - s4 * s1 * s10 + s4 * s2 * s9 + s8  * s1 * s6 - s8  * s2 * s5;

	double det = s0 * matrix.data[0][0] + s1 * matrix.data[1][0] + s2 * matrix.data[2][0] + s3 * matrix.data[3][0];
	if (det != 0.0)
	{
		det = 1.0 / det;
	}

	return matrix*det;
}

void TMatrix::SetElement(const int row, const int column, const double InData)
{
	if (row >= 0 && row <= 3 && column >= 0 && column <= 3)
	{
		data[row][column] = InData;
	}
}

TMatrix TMatrix::IndentityMatrix()
{
	TMatrix matrix;

	matrix.data[0][0] = 1;
	matrix.data[1][1] = 1;
	matrix.data[2][2] = 1;
	matrix.data[3][3] = 1;

	return matrix;
}

TMatrix TMatrix::Translate(float x, float y, float z) 
{
	TMatrix matrix = IndentityMatrix();

	matrix[3][0] = x;
	matrix[3][1] = y;
	matrix[3][2] = z;

	return matrix;
}

TMatrix TMatrix::Translate(const TVector3& In)
{
	TMatrix matrix = IndentityMatrix();

	matrix[3][0] = In.x;
	matrix[3][1] = In.y;
	matrix[3][2] = In.z;

	return matrix;
}

TMatrix TMatrix::Scale(float x, float y, float z)
{
	TMatrix matrix;

	matrix[0][0] = x;
	matrix[1][1] = y;
	matrix[2][2] = z;
	matrix[3][3] = 1;

	return matrix;
}

TMatrix TMatrix::Scale(const TVector3& In)
{
	TMatrix matrix;

	matrix[0][0] = In.x;
	matrix[1][1] = In.y;
	matrix[2][2] = In.z;
	matrix[3][3] = 1;

	return matrix;
}

TMatrix TMatrix::Rotate(float degree, const TVector3& axis)
{	
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	float x2 = axis.x*axis.x;
	float y2 = axis.y*axis.y;
	float z2 = axis.z*axis.z;
	float rad = DegreeToRadians(degree);
	float c = cosf(rad);
	float s = sinf(rad);
	float omc = 1.0f - c;

	TMatrix matrix(TVector3(x2*omc + c, y*x*omc + z*s, x*z*omc - y*s),
		TVector3(x*y*omc - z*s, y2*omc + c, y*z*omc + x*s),
		TVector3(x*y*omc + y*s, y*z*omc - x*s, z2*omc + c),
		TVector3(0, 0, 0));

	return matrix;
}

TMatrix TMatrix::Perspertive(const float fovy, const float aspect, const float near, const float far)
{
	float q = 1.0f / tan(DegreeToRadians(fovy*0.5f));
	float A = q / aspect;
	float B = (near + far) / (near - far);
	float C = (2.0f*near*far) / (near - far);

	TMatrix matrix;

	matrix.data[0][0] = A;
	matrix.data[1][1] = q;
	matrix.data[2][2] = B;
	matrix.data[3][2] = C;
	matrix.data[2][3] = -1.0f;

	return matrix;
}

TMatrix TMatrix::Ortho(float left, float right, float bottom, float top, float n, float f)
{
	TMatrix matrix;

	matrix.data[0][0] = 2.0F / (right - left);
	matrix.data[1][1] = 2.0F / (top - bottom);
	matrix.data[2][2] = 2.0F / (n - f);
	matrix.data[3][0] = (left + right) / (left - right);
	matrix.data[3][1] = (bottom + top) / (bottom - top);
	matrix.data[3][2] = (n + f) / (f - n);
	matrix.data[3][3] = 1.0f;

	return matrix;
}

TMatrix TMatrix::LookAt(const TVector3& eye, const TVector3& center, const TVector3& up)
{
	auto f = (center - eye).GetNormal();
	auto upN = up.GetNormal();
	auto s = TVector3::Cross(f, upN);
	auto u = TVector3::Cross(s, f);

	TMatrix m(TVector3(s.x, u.x, -f.x),
		TVector3(s.y, u.y, -f.y),
		TVector3(s.z, u.z, -f.z),
		TVector3(0, 0, 0));
	m[3][3] = 1;

	return m*Translate(-eye);
}
