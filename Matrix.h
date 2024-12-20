#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cassert>
#include <cmath>
class Matrix {
public:
	static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	static Matrix4x4 MakeRotateXMatrix(float radian);
	static Matrix4x4 MakeRotateYMatrix(float radian);
	static Matrix4x4 MakeRotateZMatrix(float radian);

	static Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	static Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& radian, const Vector3& translate);

	static Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);


};

Vector3& operator+=(Vector3& lhs, const Vector3& rhv);