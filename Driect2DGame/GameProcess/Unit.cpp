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
#include "BarUI.h"

Unit::Unit()
	:MonoBehaviour(typeid(this).name())
	,m_isSelect(false)
	,m_movement(nullptr)
	,m_infomation{}
	,m_hpBar(nullptr)
	,m_target(nullptr)
	,m_attack(nullptr)
	,m_unitSensor(nullptr)
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

	m_attack = GetComponent<UnitAttack>();

	m_unitSensor = GetComponent<UnitSensor>();

	m_hpBar = GetComponent<BarUI>();
}

void Unit::Finalize()
{
}

void Unit::Initalize(UnitInfomaiton _info)
{
	m_infomation = std::move(_info);

	assert(m_infomation.maxHP >= 0.f);

	// ü�� ����
	FMath::Clamp(m_infomation.currentHP, 0.f, m_infomation.maxHP);
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
	// ü�¹� ������Ʈ 
	UpdateHpBar();

	// ü���� ������ ������ �����Ѵ�
	if (m_infomation.currentHP <= 0.f)
	{
		GetGameObject()->Destory();
		return;
	}

	if (m_target != nullptr)
	{
		if (!m_target->IsAlive())
		{
			m_target = nullptr;
			m_infomation.state = UNIT_STATE::HOLD;
		}
	}

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

void Unit::TakeDamage(float _damage)
{
	m_infomation.currentHP -= _damage;

	// ü��  ����
	FMath::Clamp(m_infomation.currentHP, 0.f, m_infomation.maxHP);
}

void Unit::UpdateHpBar()
{
	if (!m_hpBar)
		return;

	// ���� ü�� ���� ���
	float ratio =  m_infomation.currentHP/ m_infomation.maxHP;

	// ü�¹� ü�º����� ���� ����
	m_hpBar->SetBarLength(ratio);
}

