﻿#include "Function.h"

void CameraControl(char* keys, Vector3& cameraPosition, Vector3& cameraRotate) {
	if (keys[DIK_Q]) {
		cameraPosition.y += 0.02f;
	}
	if (keys[DIK_E]) {
		cameraPosition.y -= 0.02f;
	}
	if (keys[DIK_A] && !keys[DIK_LSHIFT]) {
		cameraPosition.x -= 0.05f;
	}
	if (keys[DIK_D] && !keys[DIK_LSHIFT]) {
		cameraPosition.x += 0.05f;
	}
	if (keys[DIK_W] && !keys[DIK_LSHIFT]) {
		cameraPosition.z += 0.05f;
	}
	if (keys[DIK_S] && !keys[DIK_LSHIFT]) {
		cameraPosition.z -= 0.05f;
	}
	if (keys[DIK_LSHIFT] && keys[DIK_W]) {
		cameraRotate.x -= 0.02f;
	}
	if (keys[DIK_LSHIFT] && keys[DIK_S]) {
		cameraRotate.x += 0.02f;
	}
	if (keys[DIK_LSHIFT] && keys[DIK_A]) {
		cameraRotate.y -= 0.02f;
	}
	if (keys[DIK_LSHIFT] && keys[DIK_D]) {
		cameraRotate.y += 0.02f;
	}
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			Novice::ScreenPrintf(x + column * kColumnWidth, (y + row * kRowHeight) + kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.2f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.2f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.2f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2)
{
	return {
		v1.x - v2.x,
		v1.y - v2.y
	};
}

float Length(const Vector2Int& v)
{
	return sqrtf(float(v.x * v.x + v.y * v.y));
}

Vector2 Normalize(const Vector2Int& v)
{
	assert(Length(v));
	return {
		v.x / Length(v),
		v.y / Length(v),
	};
}

Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3 operator*(float scalar, const Vector3& v)
{
	Vector3 result{};
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

float Dot(const Vector3& v1, const Vector3& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float Length(const Vector3& v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Normalize(const Vector3& v)
{
	assert(Length(v));
	return {
		v.x / Length(v),
		v.y / Length(v),
		v.z / Length(v)
	};
}

Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	return { (v1.y * v2.z) - (v1.z * v2.y) , (v1.z * v2.x) - (v1.x * v2.z),(v1.x * v2.y) - (v1.y * v2.x) };
}

Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	Vector3 normalV2 = Normalize(v2);
	return {
		(v1.x * v2.x * normalV2.x) / Length(v2),
		(v1.y * v2.y * normalV2.y) / Length(v2),
		(v1.z * v2.z * normalV2.z) / Length(v2),
	};
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	return point + segment.diff;
}

Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;
}

Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
}

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

Matrix4x4 Inverse(const Matrix4x4& m)
{
	Matrix4x4 result{};
	float det =
		(m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2])
		- (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2])
		- (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2])
		+ (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2])
		+ (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2])
		- (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2])
		- (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0])
		+ (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	result.m[0][0] = ((m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[1][3] * m.m[2][1] * m.m[3][2])
		- (m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[1][1] * m.m[2][3] * m.m[3][2])) / det;
	result.m[0][1] = (-(m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[2][1] * m.m[3][2])
		+ (m.m[0][3] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[2][3] * m.m[3][2])) / det;
	result.m[0][2] = ((m.m[0][1] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[3][2])
		- (m.m[0][3] * m.m[1][2] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[3][2])) / det;
	result.m[0][3] = (-(m.m[0][1] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][1]) - (m.m[0][3] * m.m[1][1] * m.m[2][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[2][1]) + (m.m[0][2] * m.m[1][1] * m.m[2][3]) + (m.m[0][1] * m.m[1][3] * m.m[2][2])) / det;

	result.m[1][0] = (-(m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[1][3] * m.m[2][0] * m.m[3][2])
		+ (m.m[1][3] * m.m[2][2] * m.m[3][0]) + (m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[1][0] * m.m[2][3] * m.m[3][2])) / det;
	result.m[1][1] = ((m.m[0][0] * m.m[2][2] * m.m[3][3]) + (m.m[0][2] * m.m[2][3] * m.m[3][0]) + (m.m[0][3] * m.m[2][0] * m.m[3][2])
		- (m.m[0][3] * m.m[2][2] * m.m[3][0]) - (m.m[0][2] * m.m[2][0] * m.m[3][3]) - (m.m[0][0] * m.m[2][3] * m.m[3][2])) / det;
	result.m[1][2] = (-(m.m[0][0] * m.m[1][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][3] * m.m[3][0]) - (m.m[0][3] * m.m[1][0] * m.m[3][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[3][0]) + (m.m[0][2] * m.m[1][0] * m.m[3][3]) + (m.m[0][0] * m.m[1][3] * m.m[3][2])) / det;
	result.m[1][3] = ((m.m[0][0] * m.m[1][2] * m.m[2][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0]) + (m.m[0][3] * m.m[1][0] * m.m[2][2])
		- (m.m[0][3] * m.m[1][2] * m.m[2][0]) - (m.m[0][2] * m.m[1][0] * m.m[2][3]) - (m.m[0][0] * m.m[1][3] * m.m[2][2])) / det;

	result.m[2][0] = ((m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[1][3] * m.m[2][0] * m.m[3][1])
		- (m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[1][0] * m.m[2][3] * m.m[3][1])) / det;
	result.m[2][1] = (-(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][1])
		+ (m.m[0][3] * m.m[2][1] * m.m[3][0]) + (m.m[0][1] * m.m[2][0] * m.m[3][3]) + (m.m[0][0] * m.m[2][3] * m.m[3][1])) / det;
	result.m[2][2] = ((m.m[0][0] * m.m[1][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][3] * m.m[3][0]) + (m.m[0][3] * m.m[1][0] * m.m[3][1])
		- (m.m[0][3] * m.m[1][1] * m.m[3][0]) - (m.m[0][1] * m.m[1][0] * m.m[3][3]) - (m.m[0][0] * m.m[1][3] * m.m[3][1])) / det;
	result.m[2][3] = (-(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][1])
		+ (m.m[0][3] * m.m[1][1] * m.m[2][0]) + (m.m[0][1] * m.m[1][0] * m.m[2][3]) + (m.m[0][0] * m.m[1][3] * m.m[2][1])) / det;

	result.m[3][0] = (-(m.m[1][0] * m.m[2][1] * m.m[3][2]) - (m.m[1][1] * m.m[2][2] * m.m[3][0]) - (m.m[1][2] * m.m[2][0] * m.m[3][1])
		+ (m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[1][1] * m.m[2][0] * m.m[3][2]) + (m.m[1][0] * m.m[2][2] * m.m[3][1])) / det;
	result.m[3][1] = ((m.m[0][0] * m.m[2][1] * m.m[3][2]) + (m.m[0][1] * m.m[2][2] * m.m[3][0]) + (m.m[0][2] * m.m[2][0] * m.m[3][1])
		- (m.m[0][2] * m.m[2][1] * m.m[3][0]) - (m.m[0][1] * m.m[2][0] * m.m[3][2]) - (m.m[0][0] * m.m[2][2] * m.m[3][1])) / det;
	result.m[3][2] = (-(m.m[0][0] * m.m[1][1] * m.m[3][2]) - (m.m[0][1] * m.m[1][2] * m.m[3][0]) - (m.m[0][2] * m.m[1][0] * m.m[3][1])
		+ (m.m[0][2] * m.m[1][1] * m.m[3][0]) + (m.m[0][1] * m.m[1][0] * m.m[3][2]) + (m.m[0][0] * m.m[1][2] * m.m[3][1])) / det;
	result.m[3][3] = ((m.m[0][0] * m.m[1][1] * m.m[2][2]) + (m.m[0][1] * m.m[1][2] * m.m[2][0]) + (m.m[0][2] * m.m[1][0] * m.m[2][1])
		- (m.m[0][2] * m.m[1][1] * m.m[2][0]) - (m.m[0][1] * m.m[1][0] * m.m[2][2]) - (m.m[0][0] * m.m[1][2] * m.m[2][1])) / det;

	return result;
}

Matrix4x4 Transpose(const Matrix4x4& m)
{
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[j][i];
		}
	}
	return result;
}

Matrix4x4 MakeIdentity4x4()
{
	Matrix4x4 result{};
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 result = MakeIdentity4x4();
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	return result;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result{};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;
	return result;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result{};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Matrix4x4 MakeRotateXMatrix(const float& radian)
{
	Matrix4x4 result{};
	result.m[0][0] = 1.0f;
	result.m[1][1] = cosf(radian);
	result.m[1][2] = sinf(radian);
	result.m[2][1] = -sinf(radian);
	result.m[2][2] = cosf(radian);
	result.m[3][3] = 1.0f;
	return result;
}
Matrix4x4 MakeRotateYMatrix(const float& radian)
{
	Matrix4x4 result{};
	result.m[0][0] = cosf(radian);
	result.m[0][2] = -sinf(radian);
	result.m[1][1] = 1.0f;
	result.m[2][0] = sinf(radian);
	result.m[2][2] = cosf(radian);
	result.m[3][3] = 1.0f;
	return result;
}
Matrix4x4 MakeRotateZMatrix(const float& radian)
{
	Matrix4x4 result{};
	result.m[0][0] = cosf(radian);
	result.m[0][1] = sinf(radian);
	result.m[1][0] = -sinf(radian);
	result.m[1][1] = cosf(radian);
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	Matrix4x4 result = MakeTranslateMatrix(translate);
	Matrix4x4 rotateXmatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYmatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZmatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZmatrix = rotateXmatrix * rotateYmatrix * rotateZmatrix;
	result.m[0][0] = scale.x * rotateXYZmatrix.m[0][0];
	result.m[0][1] = scale.x * rotateXYZmatrix.m[0][1];
	result.m[0][2] = scale.x * rotateXYZmatrix.m[0][2];
	result.m[1][0] = scale.y * rotateXYZmatrix.m[1][0];
	result.m[1][1] = scale.y * rotateXYZmatrix.m[1][1];
	result.m[1][2] = scale.y * rotateXYZmatrix.m[1][2];
	result.m[2][0] = scale.z * rotateXYZmatrix.m[2][0];
	result.m[2][1] = scale.z * rotateXYZmatrix.m[2][1];
	result.m[2][2] = scale.z * rotateXYZmatrix.m[2][2];
	return result;
}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 result{};
	result.m[0][0] = 2 / (right - left);
	result.m[1][1] = 2 / (top - bottom);
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result{};
	assert(nearClip != 0);
	result.m[0][0] = (1 / tanf(fovY / 2)) / aspectRatio;
	result.m[1][1] = 1 / tanf(fovY / 2);
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;
	result.m[3][2] = -(nearClip * farClip) / (farClip - nearClip);
	return result;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result{};
	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -(height / 2.0f);
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + (width / 2.0f);
	result.m[3][1] = top + (height / 2.0f);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;
	return result;
}

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const float kGridHalfWidth = 2.0f;	//Gridの半分の幅
	const uint32_t kSubDivision = 10;	//分割数
	const float kGridEveryLength = (kGridHalfWidth * 2.0f) / float(kSubDivision);//1つ分の長さ = 0.4

	for (uint32_t xIndex = 0; xIndex <= kSubDivision; xIndex++)
	{
		// -半分、+Gridの半分
		float x = -kGridHalfWidth + (xIndex * kGridEveryLength);
		Vector3 start = { x,0.0f,-kGridHalfWidth };
		Vector3 end = { x,0.0f,kGridHalfWidth };

		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, 0xAAAAAAFF);
		if (xIndex == 5) {
			Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, BLACK);
		}
	}
	for (uint32_t zIndex = 0; zIndex <= kSubDivision; zIndex++)
	{
		// -半分、+Gridの半分
		float z = -kGridHalfWidth + (zIndex * kGridEveryLength);
		Vector3 start = { -kGridHalfWidth,0.0f,z };
		Vector3 end = { kGridHalfWidth,0.0f,z };

		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, 0xAAAAAAFF);
		if (zIndex == 5) {
			Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, BLACK);
		}
	}
}

void DrawSegment(const Segment& segment, Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 start = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 end = Transform(Transform(segment.origin + segment.diff, viewProjectionMatrix), viewportMatrix);
	Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const float pi = (float)std::numbers::pi;
	const uint32_t kSubDivision = 16;//分割数
	const float kLonEvery = pi / kSubDivision;;//経度分割1つ分の角度
	const float kLatEvery = (2 * pi) / kSubDivision;;//緯度分割1つ分の角度
	//緯度の方向に分割 -π/2 ～ π/2
	for (uint32_t latIndex = 0; latIndex < kSubDivision; latIndex++) {
		float lat = (-pi / 2.0f) + (kLatEvery * latIndex);//現在の緯度
		//経度の方向に分割 0～2π
		for (uint32_t lonIndex = 0; lonIndex < kSubDivision; lonIndex++) {
			float lon = lonIndex * kLonEvery;//現在の経度

			//World座標系でのa,b,cを求める

			Vector3 a, b, c;
			a = { sphere.radius * (cosf(lat) * cosf(lon)) + sphere.center.x,sphere.radius * (sinf(lat)) + sphere.center.y,
				sphere.radius * (cosf(lat) * sinf(lon)) + sphere.center.z };
			b = { sphere.radius * (cosf(lat + kLatEvery) * cosf(lon)) +
				sphere.center.x,sphere.radius * (sinf(lat + kLatEvery)) + sphere.center.y,
				sphere.radius * (cosf(lat + kLatEvery) * sinf(lon)) + sphere.center.z };
			c = { sphere.radius * (cosf(lat) * cosf(lon + kLonEvery)) + sphere.center.x,sphere.radius * (sinf(lat)) + sphere.center.y,
				sphere.radius * (cosf(lat) * sinf(lon + kLonEvery)) + sphere.center.z };
			//a,b,cをScreen座標系まで変換
			Vector3 screenA = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 screenB = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 screenC = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);
			//ab,bcで線を引く
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), color);
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenC.x), int(screenC.y), color);
		}
	}
}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 center = plane.distance * plane.normal;
	Vector3 perpendiculars[4]{};
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };

	Vector3 points[4]{};
	for (int32_t index = 0; index < 4; index++) {
		Vector3 extend = 2.0f * perpendiculars[index];
		Vector3 point = center + extend;
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color);
}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 screenVertics[3]{};
	for (int i = 0; i < 3; i++) {
		screenVertics[i] = Transform(Transform(triangle.vertics[i], viewProjectionMatrix), viewportMatrix);
	}
	Novice::DrawTriangle(int(screenVertics[0].x), int(screenVertics[0].y), int(screenVertics[1].x), int(screenVertics[1].y),
		int(screenVertics[2].x), int(screenVertics[2].y), color, kFillModeWireFrame);
}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 bottom[4]{};
	for (int i = 0; i < 4; i++){
		bottom[i] = aabb.min;
	}
	bottom[1].z += aabb.max.z;
	bottom[2] = { aabb.min.x + aabb.max.x,bottom[2].y,aabb.min.z + aabb.max.z};
	bottom[3].x += aabb.max.x;

	Vector3 top[4]{};
	for (int i = 0; i < 4; i ++ ) {
		top[i] = aabb.min;
		top[i].y += aabb.max.y;
	}
	top[1].z += aabb.max.z;
	top[2] = { aabb.min.x + aabb.max.x,top[2].y,aabb.min.z + aabb.max.z};
	top[3].x += aabb.max.x;

	Vector3 screenBot[4]{};
	Vector3 screenTop[4]{};
	for (int i = 0; i < 4; i++) {
		screenBot[i] = Transform(Transform(bottom[i], viewProjectionMatrix), viewportMatrix);
		screenTop[i] = Transform(Transform(top[i], viewProjectionMatrix), viewportMatrix);
	}

	for (int i = 0; i < 3; i ++) {
		Novice::DrawLine(int(screenBot[i].x), int(screenBot[i].y), int(screenBot[i + 1].x), int(screenBot[i + 1].y), color);
		Novice::DrawLine(int(screenTop[i].x), int(screenTop[i].y), int(screenTop[i + 1].x), int(screenTop[i + 1].y), color);
	}
	Novice::DrawLine(int(screenBot[3].x), int(screenBot[3].y), int(screenBot[0].x), int(screenBot[0].y), color);
	Novice::DrawLine(int(screenTop[3].x), int(screenTop[3].y), int(screenTop[0].x), int(screenTop[0].y), color);
	for (int i = 0; i < 4; i++) {
		Novice::DrawLine(int(screenBot[i].x), int(screenBot[i].y), int(screenTop[i].x), int(screenTop[i].y), color);
	}
}

bool IsCollideSphere(const Sphere& sphere1, const Sphere& sphere2)
{
	float distance = Length(sphere2.center - sphere1.center);
	if (distance <= sphere1.radius + sphere2.radius) {
		return true;
	}
	return false;
}

Vector3 Perpendicular(const Vector3& vector)
{
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}

bool IsCollideSpherePlane(const Sphere& sphere, const Plane& plane)
{
	float distance = (Dot(plane.normal, sphere.center) - plane.distance);
	if (fabsf(distance) - sphere.radius <= 0) {
		return true;
	}
	return false;
}

bool IsCollideLinePlane(const Segment& segment, const Plane& plane)
{
	float dot = Dot(plane.normal, segment.diff);
	if (dot == 0.0f) { return false; }	// when perpendicular -> never colliding

	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;
	if (t >= 0 && t <= 1.0f) { return true; }

	return false;
}

bool IsCollideTriangleLine(const Triangle& triangle, const Segment& segment)
{
	// cross(vector1,vector2)↓
	Vector3 normal = Normalize(Cross((triangle.vertics[1] - triangle.vertics[0]), (triangle.vertics[2] - triangle.vertics[1])));
	float dot = Dot(normal, segment.diff);
	if (dot == 0.0f) { return false; }	// when perpendicular -> never colliding
	float t = (Dot(triangle.vertics[0], normal) - Dot(segment.origin, normal)) / dot;

	Vector3 p = segment.origin + t * segment.diff;
	Vector3 v01 = triangle.vertics[1] - triangle.vertics[0];
	Vector3 v12 = triangle.vertics[2] - triangle.vertics[1];
	Vector3 v20 = triangle.vertics[0] - triangle.vertics[2];
	Vector3 v0p = p - triangle.vertics[0];
	Vector3 v1p = p - triangle.vertics[1];
	Vector3 v2p = p - triangle.vertics[2];

	Vector3 cross01 = Cross(v01, v1p);
	Vector3 cross12 = Cross(v12, v2p);
	Vector3 cross20 = Cross(v20, v0p);

	if (Dot(cross01, normal) >= 0.0f && Dot(cross12, normal) >= 0.0f && Dot(cross20, normal) >= 0.0f) {
		return true;
	}
	return false;
}

bool IsCollideAABB(const AABB& a, const AABB& b)
{
	if ((a.min.x <= b.max.x && a.max.x >= b.min.x) && 
		(a.min.y <= b.max.y && a.max.y >= b.min.y) &&
		(a.min.z <= b.max.z && a.max.z >= b.min.z)) 
	{
		return true;
	}
	else { return false; }
}
