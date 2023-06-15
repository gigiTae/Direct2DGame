
#include "GameProcessPCH.h"
#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider()
	:m_ID(CollisionManager::GetColliderID()) 
	,m_owner(nullptr)
{
}

Collider::~Collider()
{
}
