#pragma once

// 2023.7.5 21:58 gitae
// D2D에서 카메라를 담당한다.
class D2DCamera
{
public:
	D2DCamera();
	~D2DCamera();
	// 카메라 회전
	void RotateCamera(float _radian);
	
	// 카메라 이동
	void MoveCamera(Vector2 _distance);
	
	// 카메라 확대 축소
	void ZoomCamera(Vector2 _scale);

	// 카메라를 기본 행렬로 초기화한다. 
	void ResetCamera();

	const D2D1_MATRIX_3X2_F& GetCameraMatrix() { return m_cameraMatrix; }
private:
	void CalculateMatrix();

private:
	float m_rotation; // 카메라 회전
	Vector2 m_scale; // 카메라 배율
	Vector2 m_position; // 카메라 좌표

	D2D1_MATRIX_3X2_F m_cameraMatrix;
};

