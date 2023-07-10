#include "GameProcessPCH.h"
#include "UnitMovement.h"

UnitMovement::UnitMovement()
	:m_moveSpeed(0.f)
	, m_gameoject(nullptr)
	,m_unitComponent(nullptr)
{

}

UnitMovement::~UnitMovement()
{

}

void UnitMovement::Initalize(GameObject* _object, Unit* _unitComponent, float _movespeed)
{
	m_gameoject = _object;
	m_unitComponent = _unitComponent;
	m_moveSpeed = _movespeed;
}
