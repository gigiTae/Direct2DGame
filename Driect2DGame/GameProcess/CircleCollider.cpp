#include "GameProcessPCH.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "Transform.h"

CircleCollider::CircleCollider()
	:m_position{}
	,m_offset{}
	,m_active(false)
	,m_owner(nullptr)
	,m_currentCollision(0)
	,m_radius(0.f)
{
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::OnCollisionEnter(const Collision& _collision, const InputManager* _inputManager)
{
}

void CircleCollider::OnCollisionExit(const Collision& _collision, const InputManager* _inputManager)
{
}

void CircleCollider::OnCollisionStay(const Collision& _collision, const InputManager* _inputManager)
{

}

void CircleCollider::FinalUpdate()
{
	// 오브젝트의 위치에 따라서 같이 콜라이더 이동
	Vector2 ownerPosition = m_owner->GetTransform()->GetPosition();
	m_position = ownerPosition + m_offset;
}

void CircleCollider::DebugRender(D2DRenderer* _d2DRenderer)
{
	_d2DRenderer->DrawEllipse(m_position, m_radius, RGB(0, 255, 0));
}

