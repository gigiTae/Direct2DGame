#pragma once

// 2023.7.5 21:58 gitae
// D2D���� ī�޶� ����Ѵ�.
class D2DCamera
{
public:
	D2DCamera();
	~D2DCamera();
	// ī�޶� ȸ��
	void RotateCamera(float _radian);
	
	// ī�޶� �̵�
	void MoveCamera(Vector2 _distance);
	
	// ī�޶� Ȯ�� ���
	void ZoomCamera(Vector2 _scale);

	// ī�޶� �⺻ ��ķ� �ʱ�ȭ�Ѵ�. 
	void ResetCamera();

	const D2D1_MATRIX_3X2_F& GetCameraMatrix() { return m_cameraMatrix; }
private:
	void CalculateMatrix();

private:
	float m_rotation; // ī�޶� ȸ��
	Vector2 m_scale; // ī�޶� ����
	Vector2 m_position; // ī�޶� ��ǥ

	D2D1_MATRIX_3X2_F m_cameraMatrix;
};

