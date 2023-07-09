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

void FlyMovement::Move(float _deltaTime)
{
	Transform* transform = m_gameoject->GetComponent<Transform>();
}
