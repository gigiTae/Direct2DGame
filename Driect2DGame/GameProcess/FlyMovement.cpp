#include "GameProcessPCH.h"
#include "FlyMovement.h"
#include "Transform.h"
#include "GameObject.h"

FlyMovement::FlyMovement()
{

}

FlyMovement::~FlyMovement()
{

}

bool FlyMovement::Move(float _deltaTime)
{
	Transform* transform = m_gameoject->GetComponent<Transform>();
	
	Vector2 position = transform->GetPosition();
	
	Vector2 direction = m_destination - position;
	
	// 근사적으로 도착했다고 판단
	if (direction.LengthSquared() <= 0.001f)
	{
		return true;
	}

	direction.Normalize();

	Vector2 distance = direction * _deltaTime * m_moveSpeed;

	transform->AddPosition(distance);

	return false;
}
