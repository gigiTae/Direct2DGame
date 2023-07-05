#include "RendererPCH.h"
#include "D2DCamera.h"

D2DCamera::D2DCamera()
	:m_cameraMatrix{}
	,m_position{0.f,0.f}
	,m_rotation(0.f)
	,m_scale{1.f,1.f}
{}

D2DCamera::~D2DCamera()
{}

void D2DCamera::RotateCamera(float _radian)
{
	// ��ũ�� ��ǥ��� ��ȯ
	m_rotation -= _radian;
	CalculateMatrix();
}

void D2DCamera::MoveCamera(Vector2 _distance)
{
	// ��ũ�� ��ǥ��� ��ȯ
	m_position += _distance.ToScreenPoint();
	CalculateMatrix();
}

void D2DCamera::ZoomCamera(Vector2 _scale)
{
	m_scale += _scale;

	constexpr float Min = 0.1f;
	constexpr float Max = 5.f;

	m_scale.x = FMath::Clamp(m_scale.x, Min, Max);
	m_scale.y = FMath::Clamp(m_scale.y, Min, Max);

	CalculateMatrix();
}

void D2DCamera::ResetCamera()
{
	m_rotation = 0.f;
	m_position = Vector2(0.f, 0.f);
	m_scale = Vector2(1.f, 1.f);

	m_cameraMatrix = D2D1::Matrix3x2F::Identity();
}

void D2DCamera::CalculateMatrix()
{
	float angle = FMath::Rad2Deg(m_rotation);
	D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(angle);
	D2D1_MATRIX_3X2_F scale = D2D1::Matrix3x2F::Scale(m_scale.x, m_scale.y);
	D2D1_MATRIX_3X2_F position = D2D1::Matrix3x2F::Translation(m_position.x, m_position.y);

	// ���� ��ȯ ���         
	m_cameraMatrix = position * rotation * scale;
}
