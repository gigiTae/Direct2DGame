#include "GameProcessPCH.h"
#include "UnitSensor.h"
#include "GameObject.h"
#include "CircleCollider.h"
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


void UnitSensor::OnTriggerEnter(const Collision& _collision)
{
	BoxCollider* box = dynamic_cast<BoxCollider*>(_collision.myCollider);
	if (box == nullptr)
		return;

	// ������ ������Ʈ�� �ʿ� �߰��Ѵ�.
	GameObject* inObj = _collision.otherObject;
	const string& name = inObj->GetName();

	auto iter = m_senseObjects.find(inObj->GetName());

	if (iter == m_senseObjects.end())
	{
		m_senseObjects.insert(std::make_pair(name, inObj));
	}

}

void UnitSensor::OnTriggerExit(const Collision& _collision)
{
	// UnitSensor���� ����� ���� ���� �����ݶ��̴����� ����� �簢�� �ݶ��̴��� ��� �����̴�.
	if (_collision.myCollider->GetColliderType() == COLLIDER_TYPE::BOX)
		return;

	if (_collision.otherCollider->GetColliderType() == COLLIDER_TYPE::CIRCLE)
		return;

	// ������ ���������� �������
	GameObject* exitObj = _collision.otherObject;

	const string& name = exitObj->GetName();

	auto iter = m_senseObjects.find(name);

	if (iter != m_senseObjects.end())
	{
		m_senseObjects.erase(iter);
	}
}
