
#include "GameProcessPCH.h"
#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider(string _name)
	:Component(CALL_ORDER::COLLIDER, _name)
	, m_ID(CollisionManager::GetColliderID())
{

}

Collider::~Collider()
{
}
