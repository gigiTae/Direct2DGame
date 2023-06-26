#include "GameProcessPCH.h"
#include "Transform.h"

Transform::Transform()
	:m_position{}
	,m_rotation(0.f)
	,m_scale{}
{
}

Transform::~Transform()
{
}

void Transform::AddRotation(float _radian)
{
	m_rotation += _radian;
	// 각도값을 조정
	if (m_rotation >= FMath::TwoPI)
	{
		m_rotation -= FMath::TwoPI;
	}

	if (m_rotation < -0.f)
	{
		m_rotation += FMath::TwoPI;
	}
}

void Transform::FinalUpdate()
{

}

void Transform::DebugRender(D2DRenderer* _d2DRenderer)
{
	Vector2 pos = GetPosition();
	float rotation = GetRotation();

	wstring info = L"\nX:" + std::to_wstring(static_cast<int>(pos.x))
		+ L"\nY:" + std::to_wstring(static_cast<int>(pos.y))
		+ L"\nAngle:" + std::to_wstring(static_cast<int>(FMath::Rad2Deg(rotation)));

	_d2DRenderer->DrawTextW(info, pos, Vector2(pos.x + 200.f, pos.y), D2D1::ColorF::Gold);
}
