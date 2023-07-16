
#include "GameProcessPCH.h"
#include "Collider.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

Collider::Collider(string _name, COLLIDER_TYPE _type)
	:Component(CALL_ORDER::COLLIDER, _name)
	,m_type(_type)
	,m_currentCollision(0)
	, m_node(nullptr)
	, m_isTrigger(false)
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

void Collider::OnTriggerEnter(const Collision& _collision)
{
	++m_currentCollision;
	assert(m_currentCollision >= 0);

	GetGameObject()->OnTriggerEnter(_collision);
}

void Collider::OnTriggerStay(const Collision& _collision)
{
	GetGameObject()->OnTriggerStay(_collision);
}

void Collider::OnTriggerExit(const Collision& _collision)
{
	--m_currentCollision;
	assert(m_currentCollision >= 0);

	GetGameObject()->OnTriggerExit(_collision);
}

bool Collider::Collides(Collider* _collider)
{
	static const string box = typeid(BoxCollider*).name();
	static const string circle = typeid(CircleCollider*).name();

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
