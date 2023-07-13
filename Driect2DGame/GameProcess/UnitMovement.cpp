#include "GameProcessPCH.h"
#include "UnitMovement.h"
#include "GameObject.h"

UnitMovement::UnitMovement(const string& _name)
	:MonoBehaviour(_name)
	,m_destination{}
	,m_unit(nullptr)
{

}

UnitMovement::~UnitMovement()
{

}

void UnitMovement::Start()
{
	//m_unit = GetComponent<Unit>();
	
}

void UnitMovement::SetDestination(Vector2 _dest)
{
	m_destination = _dest;
}
