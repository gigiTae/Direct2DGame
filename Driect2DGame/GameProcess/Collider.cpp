
#include "GameProcessPCH.h"
#include "Collider.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

Collider::Collider(string _name)
	:Component(CALL_ORDER::COLLIDER, _name)
	,m_currentCollision(0)
	, m_node(nullptr)
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

bool Collider::Collides(Collider* _collider)
{
	static const string box = typeid(BoxCollider).name();
	static const string circle = typeid(CircleCollider).name();

	const string& name = _collider->GetName();


	if (name == box)
	{
		return Collides(dynamic_cast<BoxCollider*>(_collider));
	}
	else if (name == circle)
	{
		return Collides(dynamic_cast<CircleCollider*>(_collider));
	}

	assert(nullptr);

	return false;
}
