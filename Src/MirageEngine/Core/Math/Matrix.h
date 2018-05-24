#pragma once
#include "Vector3.h"
#include "MEMath.h"
#include <string.h>

namespace MirageMath
{
	//----------------------------------------------------------
	//Matrix for 4x4
	//----------------------------------------------------------

	template<class T>
	struct alignas(16) Matrix4x4
	{
	public:
		Matrix4x4()
		{
			memset(data, 0, sizeof(T) * 16);
		}
		Matrix4x4(Vector3<T>& InX, Vector3<T>& InY, Vector3<T>& InZ, Vector3<T>& InW)
		{
			data[0][0] = InX.x; data[0][1] = InX.y; data[0][2] = InX.z; data[0][3] = 0;
			data[1][0] = InY.x; data[1][1] = InY.y; data[1][2] = InY.z; data[1][3] = 0;
			data[2][0] = InZ.x; data[2][1] = InZ.y; data[2][2] = InZ.z; data[2][3] = 0;
			data[3][0] = InW.x; data[3][1] = InW.y; data[3][2] = InW.z; data[3][3] = 1;
		}
		Matrix4x4(Vector3<T>&& InX, Vector3<T>&& InY, Vector3<T>&& InZ, Vector3<T>&& InW)
		{
			data[0][0] = InX.x; data[0][1] = InX.y; data[0][2] = InX.z; data[0][3] = 0;
			data[1][0] = InY.x; data[1][1] = InY.y; data[1][2] = InY.z; data[1][3] = 0;
			data[2][0] = InZ.x; data[2][1] = InZ.y; data[2][2] = InZ.z; data[2][3] = 0;
			data[3][0] = InW.x; data[3][1] = InW.y; data[3][2] = InW.z; data[3][3] = 1;
		}
		Matrix4x4(const Matrix4x4& In)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					data[i][j] = In.data[i][j];
				}
			}
		}

		Matrix4x4 operator + (const Matrix4x4& InM) const
		{
			Matrix4x4 matrix;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					matrix.data[i][j] = data[i][j] + InM.data[i][j];
				}
			}
			return matrix;
		}
		Matrix4x4 operator - (const Matrix4x4& InM) const
		{
			Matrix4x4 matrix;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					matrix.data[i][j] = data[i][j] - InM.data[i][j];
				}
			}
			return matrix;
		}
		Matrix4x4 operator * (const Matrix4x4& InM) const
		{
			Matrix4x4 matrix;
			for (int i = 0; i < 4; i++)
			{
				for (int k = 0; k < 4; k++)
				{
					for (int j = 0; j < 4; j++)
					{
						matrix.data[i][k] += data[i][j] * InM.data[j][k];
					}
				}
			}
			return matrix;
		}
		Matrix4x4 operator * (double In) const
		{
			Matrix4x4 matrix;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					matrix.data[i][j] = data[i][j] * In;
				}
			}
			return matrix;
		}
		void operator = (const Matrix4x4& In)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					data[i][j] = In.data[i][j];
				}
			}
		}
		T* const operator[](const int In)
		{
			return data[In];
		}
		Matrix4x4 Inverse() {
			Matrix4x4 matrix;
			const T s0 = (data[0][0]); const T s1 = (data[0][1]); const T s2 = (data[0][2]); const T s3 = (data[0][3]);
			const T s4 = (data[1][0]); const T s5 = (data[1][1]); const T s6 = (data[1][2]); const T s7 = (data[1][3]);
			const T s8 = (data[2][0]); const T s9 = (data[2][1]); const T s10 = (data[2][2]); const T s11 = (data[2][3]);
			const T s12 = (data[3][0]); const T s13 = (data[3][1]); const T s14 = (data[3][2]); const T s15 = (data[3][3]);

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

			T det = s0 * matrix.data[0][0] + s1 * matrix.data[1][0] + s2 * matrix.data[2][0] + s3 * matrix.data[3][0];
			if (det != 0.0)
			{
				det = 1.0 / det;
			}

			return matrix*det;
		}

		void SetElement(const int row, const int column, const T InData)
		{
			if (row >= 0 && row <= 3 && column >= 0 && column <= 3)
			{
				data[row][column] = InData;
			}
		}

		static Matrix4x4<T> IndentityMatrix()
		{
			Matrix4x4<T> matrix;

			matrix.data[0][0] = 1;
			matrix.data[1][1] = 1;
			matrix.data[2][2] = 1;
			matrix.data[3][3] = 1;

			return matrix;
		}
		static Matrix4x4<T> Translate(T x, T y, T z)
		{
			Matrix4x4<T> matrix = IndentityMatrix();

			matrix[3][0] = x;
			matrix[3][1] = y;
			matrix[3][2] = z;

			return matrix;
		}
		static Matrix4x4<T> Translate(const Vector3<T>& In)
		{
			Matrix4x4<T> matrix = IndentityMatrix();

			matrix[3][0] = In.x;
			matrix[3][1] = In.y;
			matrix[3][2] = In.z;

			return matrix;
		}
		static Matrix4x4<T> Scale(T x, T y, T z)
		{
			Matrix4x4<T> matrix;

			matrix[0][0] = x;
			matrix[1][1] = y;
			matrix[2][2] = z;
			matrix[3][3] = 1;

			return matrix;
		}
		static Matrix4x4<T> Scale(const Vector3<T>& In)
		{
			Matrix4x4<T> matrix;

			matrix[0][0] = In.x;
			matrix[1][1] = In.y;
			matrix[2][2] = In.z;
			matrix[3][3] = 1;

			return matrix;
		}
		static Matrix4x4<T> Rotate(T degree, const Vector3<T>& axis)
		{
			float x = axis.x;
			float y = axis.y;
			float z = axis.z;
			float x2 = axis.x*axis.x;
			float y2 = axis.y*axis.y;
			float z2 = axis.z*axis.z;
			float rad = DegreeToRadians(degree);
			float c = std::cos(rad);
			float s = std::sin(rad);
			float omc = 1.0f - c;

			Matrix4x4<T> matrix(Vector3<T>(x2*omc + c, y*x*omc + z*s, x*z*omc - y*s),
				Vector3<T>(x*y*omc - z*s, y2*omc + c, y*z*omc + x*s),
				Vector3<T>(x*y*omc + y*s, y*z*omc - x*s, z2*omc + c),
				Vector3<T>(0, 0, 0));

			return matrix;
		}
		static Matrix4x4<T> Perspertive(const T fovy, const T aspect, const T near, const T far)
		{
			float q = 1.0f / tan(DegreeToRadians(fovy*0.5f));
			float A = q / aspect;
			float B = (near + far) / (near - far);
			float C = (2.0f*near*far) / (near - far);

			Matrix4x4<T> matrix;

			matrix.data[0][0] = A;
			matrix.data[1][1] = q;
			matrix.data[2][2] = B;
			matrix.data[3][2] = C;
			matrix.data[2][3] = -1.0f;

			return matrix;
		}
		static Matrix4x4<T> Ortho(T left, T right, T bottom, T top, T n, T f)
		{
			Matrix4x4<T> matrix;

			matrix.data[0][0] = 2.0f / (right - left);
			matrix.data[1][1] = 2.0f / (top - bottom);
			matrix.data[2][2] = 2.0f / (n - f);
			matrix.data[3][0] = (left + right) / (left - right);
			matrix.data[3][1] = (bottom + top) / (bottom - top);
			matrix.data[3][2] = (n + f) / (f - n);
			matrix.data[3][3] = 1.0f;

			return matrix;
		}
		static Matrix4x4<T> LookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up)
		{
			auto f = (center - eye).GetNormal();
			auto upN = up.GetNormal();
			auto s = Vector3<T>::Cross(f, upN);
			auto u = Vector3<T>::Cross(s, f);

			Matrix4x4<T> m(Vector3<T>(s.x, u.x, -f.x),
				Vector3<T>(s.y, u.y, -f.y),
				Vector3<T>(s.z, u.z, -f.z),
				Vector3<T>(0, 0, 0));
			m[3][3] = 1;

			return m*Translate(-eye);
		}

	private:

		T data[4][4];
	};

	template<class T, class F>
	MEINLINE Matrix4x4<T> operator * (const F InValue, const Matrix4x4<T>& In)
	{
		return In*InValue;
	}

	typedef Matrix4x4<f32> Matrix4x4f;
	typedef Matrix4x4<f64> Matrix4x4F;

	//----------------------------------------------------------
	//Matrix for 3x3
	//----------------------------------------------------------

	template<class T>
	struct alignas(8) Matrix3x3
	{
	public:
		Matrix3x3()
		{
			memset(data, 0, sizeof(T) * 9);
		}
		Matrix3x3(Vector3<T>& InX, Vector3<T>& InY, Vector3<T>& InZ)
		{
			data[0][0] = InX.x; data[0][1] = InX.y; data[0][2] = InX.z;
			data[1][0] = InY.x; data[1][1] = InY.y; data[1][2] = InY.z;
			data[2][0] = InZ.x; data[2][1] = InZ.y; data[2][2] = InZ.z;
		}
		Matrix3x3(Vector3<T>&& InX, Vector3<T>&& InY, Vector3<T>&& InZ)
		{
			data[0][0] = InX.x; data[0][1] = InX.y; data[0][2] = InX.z;
			data[1][0] = InY.x; data[1][1] = InY.y; data[1][2] = InY.z;
			data[2][0] = InZ.x; data[2][1] = InZ.y; data[2][2] = InZ.z;
		}
		Matrix3x3(const Matrix3x3& In)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					data[i][j] = In.data[i][j];
				}
			}
		}

		Matrix3x3 operator + (const Matrix3x3& InM) const
		{
			Matrix3x3 matrix;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					matrix.data[i][j] = data[i][j] + InM.data[i][j];
				}
			}
			return matrix;
		}
		Matrix3x3 operator - (const Matrix3x3& InM) const
		{
			Matrix3x3 matrix;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					matrix.data[i][j] = data[i][j] - InM.data[i][j];
				}
			}
			return matrix;
		}
		Matrix3x3 operator * (const Matrix3x3& InM) const
		{
			Matrix3x3 matrix;
			for (int i = 0; i < 3; i++)
			{
				for (int k = 0; k < 3; k++)
				{
					for (int j = 0; j < 3; j++)
					{
						matrix.data[i][k] += data[i][j] * InM.data[j][k];
					}
				}
			}
			return matrix;
		}
		Matrix3x3 operator * (double In) const
		{
			Matrix3x3 matrix;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					matrix.data[i][j] = data[i][j] * In;
				}
			}
			return matrix;
		}
		void operator = (const Matrix3x3& In)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					data[i][j] = In.data[i][j];
				}
			}
		}
		T* const operator[](const int In)
		{
			return data[In];
		}
		Matrix3x3 Inverse()
		{
			Matrix3x3 matrix;
			const T s00 = (data[0][0]); const T s01 = (data[0][1]); const T s02 = (data[0][2]); 
			const T s10 = (data[1][0]); const T s11 = (data[1][1]); const T s12 = (data[1][2]); 
			const T s20 = (data[2][0]); const T s21 = (data[2][1]); const T s22 = (data[2][2]);

			matrix.data[0][0] = s22*s11-s12*s21;
			matrix.data[0][1] = s02*s21-s22*s01;
			matrix.data[0][2] = s12*s01-s02*s11;
			matrix.data[1][0] = s12*s20-s22*s10;
			matrix.data[1][1] = s22*s00-s02*s20;
			matrix.data[1][2] = s02*s10-s12*s00;
			matrix.data[2][0] = s10*s21-s20*s11;
			matrix.data[2][1] = s20*s01-s00*s21;
			matrix.data[2][2] = s00*s11-s10*s01;

			T det = s00 * matrix.data[0][0] + s10 * matrix.data[1][0] + s20 * matrix.data[2][0];
			if (det != 0.0)
			{
				det = 1.0 / det;
			}

			return matrix*det;
		}

		void SetElement(const int row, const int column, const T InData)
		{
			if (row >= 0 && row <= 3 && column >= 0 && column <= 3)
			{
				data[row][column] = InData;
			}
		}

		static Matrix3x3<T> IndentityMatrix()
		{
			Matrix3x3<T> matrix;

			matrix.data[0][0] = 1;
			matrix.data[1][1] = 1;
			matrix.data[2][2] = 1;
			
			return matrix;
		}

		static Matrix3x3<T> Scale(T x, T y, T z)
		{
			Matrix3x3<T> matrix;

			matrix[0][0] = x;
			matrix[1][1] = y;
			matrix[2][2] = z;

			return matrix;
		}
		static Matrix3x3<T> Scale(const Vector3<T>& In)
		{
			Matrix3x3<T> matrix;

			matrix[0][0] = In.x;
			matrix[1][1] = In.y;
			matrix[2][2] = In.z;

			return matrix;
		}
		static Matrix3x3<T> Rotate(T degree, const Vector3<T>& axis)
		{
			float x = axis.x;
			float y = axis.y;
			float z = axis.z;
			float x2 = axis.x*axis.x;
			float y2 = axis.y*axis.y;
			float z2 = axis.z*axis.z;
			float rad = DegreeToRadians(degree);
			float c = std::cos(rad);
			float s = std::sin(rad);
			float omc = 1.0f - c;

			Matrix3x3<T> matrix(Vector3<T>(x2*omc + c, y*x*omc + z*s, x*z*omc - y*s),
				Vector3<T>(x*y*omc - z*s, y2*omc + c, y*z*omc + x*s),
				Vector3<T>(x*y*omc + y*s, y*z*omc - x*s, z2*omc + c));

			return matrix;
		}
		
		static Matrix3x3<T> LookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up)
		{
			auto f = (center - eye).GetNormal();
			auto upN = up.GetNormal();
			auto s = Vector3<T>::Cross(f, upN);
			auto u = Vector3<T>::Cross(s, f);

			Matrix3x3<T> m(Vector3<T>(s.x, u.x, -f.x),
				Vector3<T>(s.y, u.y, -f.y),
				Vector3<T>(s.z, u.z, -f.z));

			return m*Translate(-eye);
		}

	private:

		T data[3][3];
	};

	template<class T, class F>
	MEINLINE Matrix3x3<T> operator * (const F InValue, const Matrix3x3<T>& In)
	{
		return In*InValue;
	}

	typedef Matrix3x3<f32> Matrix3x3f;
	typedef Matrix3x3<f64> Matrix3x3F;
}