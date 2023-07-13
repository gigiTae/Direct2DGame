#include "GameProcessPCH.h"
#include "Unit.h"
#include "Transform.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "UnitMovement.h"
#include "RigidBody.h"
#include "CircleCollider.h"
#include "Collider.h"
#include "Transform.h"
#include "UnitSensor.h"
#include "UnitAttack.h"

Unit::Unit()
	:MonoBehaviour(typeid(this).name())
	,m_isSelect(false)
	,m_movement(nullptr)
	,m_infomation{}
{

}

Unit::~Unit()
{

}

void Unit::Start()
{
    // ������ ������Ʈ�� ����

	m_movement = GetComponent<UnitMovement>();
	assert(m_movement);

	m_unitSensor = GetComponent<UnitSensor>();
	assert(m_unitSensor);

	m_attack = GetComponent<UnitAttack>();
	assert(m_attack);


}

void Unit::Finalize()
{
}

void Unit::Initalize(UnitInfomaiton _info)
{
	m_infomation = std::move(_info);
}

void Unit::PreRender(D2DRenderer* _d2DRenderer)
{
	// ������ Contoroller�� ���ؼ� ������ �Ȱ�� �Ʒ��� �����׷��� ǥ���Ѵ�.
	if (!m_isSelect)
	{
		return;
	}

	Transform* transform = GetComponent<Transform>();
	Vector2 position = transform->GetPosition();
	Vector2 scale = transform->GetScale();
	position.y -= scale.y *0.5f;

	scale.y *= 0.25f;
	scale.x *= 0.5f;

	_d2DRenderer->DrawEllipse(position, scale, D2D1::ColorF::Green);

}

void Unit::Update(float _deltaTime)
{
	

	switch (m_infomation.state)
	{
		case UNIT_STATE::HOLD:
			break;
		case UNIT_STATE::HOLD_ATTACK:
		{
			m_attack->Attack(m_target);

			// ���ο� Ÿ���� ã�´�.
			if (!m_unitSensor->IsSeneseUnit(m_target))
			{

			}
		}
			break;
		case UNIT_STATE::TRACK:
		{
			Vector2 targetPos = m_target->GetComponent<Transform>()->GetPosition();
			m_movement->SetDestination(targetPos);
			m_movement->Move(_deltaTime);

			// ���ݹ������� ���� �����Ѵ�
			if (m_unitSensor->IsSeneseUnit(m_target))
			{
				m_infomation.state = UNIT_STATE::ATTACK;
			}
		}
			break;
		case UNIT_STATE::ATTACK:
		{
			// ���� �����Ѵ�
			m_attack->Attack(m_target);

			// ���ݹ��� �����ΰ��� �����Ѵ�.
			if (!m_unitSensor->IsSeneseUnit(m_target))
			{
				m_infomation.state = UNIT_STATE::TRACK;
			}
		}
			break;
		case UNIT_STATE::MOVE:
		{
			bool isArrive = m_movement->Move(_deltaTime);

			if (isArrive)
			{
				m_infomation.state = UNIT_STATE::HOLD;
			}
		}
			break;
		case UNIT_STATE::DEAD:
		{
			// ������ �����Ѵ�.
			GetGameObject()->Destory();
		}
			break;
		default:
			break;
	}
}


void Unit::AttackUnit(GameObject* _unit)
{
	m_target = _unit;

	// ���� ��Ÿ����� Ÿ���� �ִ°�� ����
	if (m_unitSensor->IsSeneseUnit(m_target))
	{
		m_infomation.state = UNIT_STATE::ATTACK;
	}
	// ���� ��Ÿ� �ۿ� Ÿ���� �ִ� ��� ���� 
	else
	{
		m_infomation.state = UNIT_STATE::TRACK;
	}
}

void Unit::MoveUnit(Vector2 _destination)
{
	m_movement->SetDestination(_destination);
	m_infomation.state = UNIT_STATE::MOVE;
}

void Unit::HoldUnit()
{
	m_infomation.state = UNIT_STATE::HOLD;
}

//void Unit::OnCollisionStay(const Collision& _collision)
//{
//
//	/// �̰Ŵ� �����ʿ��� �ϴ°ɷ� ����
	//RigidBody* rigid = GetComponent<RigidBody>();

	//Transform* transform = GetComponent<Transform>();
	//Transform* otherTransform = _collision.otherObject->GetComponent<Transform>();

	//Vector2 position = transform->GetPosition();
	//Vector2 otherPos = otherTransform->GetPosition();

	//Vector2 direct = position - otherPos;
	//direct.Normalize();

	//float otherMass = rigid->GetMass();
	//if (otherMass == FLT_MAX) // ������ ������Ʈ 
	//{
	//	float otherRadius = _collision.otherObject->GetComponent<CircleCollider>()->GetRadius();
	//	float radius = GetComponent<CircleCollider>()->GetRadius();

	//	Vector2 pushDistance = direct * (otherRadius + radius - (position - otherPos).Length());

	//	transform->AddPosition(pushDistance);
	//}
	//else // �����̴� ������Ʈ
	//{
	//	//return;
	//	// ������ ���� ��ġ�� ������ ������ �������� �о�� 
	//	if (direct == Vector2::Zero)
	//	{
	//	}
	//	constexpr float power = 500.f;
	//	Vector2 force = direct * power;

	//	rigid->AddForce(force);
	//}

