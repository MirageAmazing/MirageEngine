#pragma once
#include "TVector3.h"

struct alignas(16) TMatrix
{
public:
	TMatrix();
	TMatrix(TVector3&, TVector3&, TVector3&, TVector3&);
	TMatrix(TVector3&&, TVector3&&, TVector3&&, TVector3&&);
	TMatrix(const TMatrix&);

	TMatrix operator + (const TMatrix&) const;
	TMatrix operator - (const TMatrix&) const;
	TMatrix operator * (const TMatrix&) const;
	TMatrix operator * (double) const;
	void operator = (const TMatrix&);
	double* const operator[](const int);
	TMatrix Inverse();

	void SetElement(const int, const int, const double);

	static TMatrix IndentityMatrix();
	static TMatrix Translate(float x, float y, float z);
	static TMatrix Translate(const TVector3& In);
	static TMatrix Scale(float x, float y, float z);
	static TMatrix Scale(const TVector3& In);
	static TMatrix Rotate(float degree, const TVector3& axis);
	static TMatrix Perspertive(const float fovy, const float aspect, const float near, const float far);
	static TMatrix Ortho(float left, float right, float bottom, float top, float n, float f);
	static TMatrix LookAt(const TVector3& eye, const TVector3& center, const TVector3& up);
private:

	double data[4][4];
};