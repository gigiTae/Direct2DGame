#include "GameProcessPCH.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameObject.h"
#include "CollisionManager.h"

CircleCollider::CircleCollider()
	:Collider(typeid(this).name())
	,m_position{}
	,m_offset{}
	,m_active(false)
	,m_radius(0.f)
{ 
}

CircleCollider::~CircleCollider()
{
}


void CircleCollider::LateUpdate(float _deltaTime)
{
	Vector2 ownerPosition = GetComponent<Transform>()->GetPosition();
	m_position = ownerPosition + m_offset;
}

void CircleCollider::DebugRender(D2DRenderer* _d2DRenderer)
{
	if (GetCurrentCollison() == 0)
	{
		_d2DRenderer->DrawEllipse(m_position, m_radius, D2D1::ColorF::LightGreen);
	}
	else
	{
		_d2DRenderer->DrawEllipse(m_position, m_radius, D2D1::ColorF::Red);
	}
}

