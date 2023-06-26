#include "GameProcessPCH.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameObject.h"
#include "CollisionManager.h"

CircleCollider::CircleCollider()
	:m_position{}
	,m_offset{}
	,m_active(false)
	,m_currentCollision(0)
	,m_radius(0.f)
{
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::OnCollisionEnter(const Collision& _collision, const InputManager* _inputManager)
{
	++m_currentCollision;
	assert(m_currentCollision >= 0);

	GetOwner()->OnCollisionEnter(_collision, _inputManager);
}

void CircleCollider::OnCollisionExit(const Collision& _collision, const InputManager* _inputManager)
{
	--m_currentCollision;
	assert(m_currentCollision >= 0);

	GetOwner()->OnCollisionExit(_collision, _inputManager);
}

void CircleCollider::OnCollisionStay(const Collision& _collision, const InputManager* _inputManager)
{
	GetOwner()->OnCollisionStay(_collision, _inputManager);
}

void CircleCollider::FinalUpdate()
{
	// ������Ʈ�� ��ġ�� ���� ���� �ݶ��̴� �̵�
	Vector2 ownerPosition = GetOwner()->GetTransform()->GetPosition();
	m_position = ownerPosition + m_offset;
}

void CircleCollider::DebugRender(D2DRenderer* _d2DRenderer)
{
	if (m_currentCollision == 0)
	{
		_d2DRenderer->DrawEllipse(m_position, m_radius, D2D1::ColorF::LightGreen);
	}
	else
	{
		_d2DRenderer->DrawEllipse(m_position, m_radius, D2D1::ColorF::Red);
	}
}

