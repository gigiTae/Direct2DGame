
#include "GameProcessPCH.h"
#include "Collider.h"
#include "GameObject.h"
#include "CollisionManager.h"

Collider::Collider(string _name)
	:Component(CALL_ORDER::COLLIDER, _name)
	,m_currentCollision(0)
	, m_ID(CollisionManager::GetColliderID())
{

}

Collider::~Collider()
{
}

void Collider::OnCollisionEnter(const Collision& _collision)
{
	++m_currentCollision;
	assert(m_currentCollision >= 0);

	GetGameObject()->OnCollisionEnter(_collision);
}

void Collider::OnCollisionExit(const Collision& _collision)
{
	--m_currentCollision;
	assert(m_currentCollision >= 0);

	GetGameObject()->OnCollisionExit(_collision);
}

void Collider::OnCollisionStay(const Collision& _collision)
{
	GetGameObject()->OnCollisionStay(_collision);
}
