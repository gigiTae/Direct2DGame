#include "GameProcessPCH.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Transform.h"

BoxCollider::BoxCollider()
	:Collider(typeid(this).name())
	,m_offset{}
	, m_position{}
	, m_rotation(0.f)
	, m_scale{}
	, m_isRotatable(false)
	, m_active(false)
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::LateUpdate(float _deltaTime)
{
	// 오브젝트의 위치에 따라서 같이 콜라이더 이동
	Vector2 ownerPosition = GetComponent<Transform>()->GetPosition();
	m_position = ownerPosition + m_offset;
	// 오브젝트 회전에 따라서 콜라이더도 같이 회전
	if (m_isRotatable)
	{
		float ownerRotation = GetComponent<Transform>()->GetRotation();
		m_rotation = ownerRotation;
	}
}

void BoxCollider::DebugRender(D2DRenderer* _d2DRenderer)
{
	Vector2 leftTop;
	leftTop.x = m_position.x + m_scale.x * 0.5f;
	leftTop.y = m_position.y + m_scale.y * 0.5f;

	Vector2 rightBottom;
	rightBottom.x = m_position.x - m_scale.x * 0.5f;
	rightBottom.y = m_position.y - m_scale.y * 0.5f;

	Vector2 postion = GetComponent<Transform>()->GetPosition();

	// 충돌상황에 따라서 랜더링
	if (GetCurrentCollison() == 0)
	{ 
		_d2DRenderer->DrawRectangle(leftTop, rightBottom,D2D1::ColorF::LightGreen);
	}
	else
	{
		_d2DRenderer->DrawRectangle(leftTop, rightBottom, D2D1::ColorF::Red);
	}
}

