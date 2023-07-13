#include "GameProcessPCH.h"
#include "UnitSensor.h"
#include "GameObject.h"
#include "BoxCollider.h"

UnitSensor::UnitSensor()
	:MonoBehaviour(typeid(this).name())
	,m_target(nullptr)
	,m_senseObjects{}
{

}

UnitSensor::~UnitSensor()
{

}

bool UnitSensor::IsSeneseUnit(GameObject* _target)
{
	auto iter = m_senseObjects.find(_target->GetName());

	if (iter != m_senseObjects.end())
		return true;

	return false;
}

void UnitSensor::Update(float _deltaTime)
{

}

void UnitSensor::OnCollisionEnter(const Collision& _collision)
{
	BoxCollider* circle =dynamic_cast<BoxCollider*>(_collision.myCollider);
	if (circle == nullptr)
		return;

	// 감지한 오브젝트를 맵에 추가한다.
	GameObject* inObj = _collision.otherObject;
	const string& name = inObj->GetName();

	auto iter= m_senseObjects.find(inObj->GetName());

	if (iter == m_senseObjects.end())
	{
		m_senseObjects.insert(std::make_pair(name, inObj));
	}

  }

void UnitSensor::OnCollisionExit(const Collision& _collision)
{
	BoxCollider* circle = dynamic_cast<BoxCollider*>(_collision.myCollider);
	if (circle == nullptr)
		return;

	// 유닛이 범위밖으로 나간경우
	GameObject* exitObj = _collision.otherObject;

	const string& name = exitObj->GetName();

	auto iter = m_senseObjects.find(name);

	if (iter != m_senseObjects.end())
	{
		m_senseObjects.erase(iter);
	}
}
