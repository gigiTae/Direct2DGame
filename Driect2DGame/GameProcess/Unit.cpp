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

Unit::Unit()
	:MonoBehaviour(typeid(this).name())
	,m_isSelect(false)
	,m_state(UNIT_STATE::HOLD)
	,m_movement(nullptr)
	,m_hp(0.f)
{

}

Unit::~Unit()
{

}

void Unit::Initalize(UnitMovement* _movement)
{
	m_movement = _movement;
	
	m_movement->Initalize(GetGameObject(), this, 200.f);
}

void Unit::Finalize()
{
	delete m_movement;

}

void Unit::PreRender(D2DRenderer* _d2DRenderer)
{
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
	switch (m_state)
	{
	case UNIT_STATE::HOLD:
	{
	}
		break;
	case UNIT_STATE::ATTACK:
	{
	}
		break;
	case UNIT_STATE::MOVE:
	{
		bool isArrive =  m_movement->Move(_deltaTime);

		if (isArrive)
		{
			m_state = UNIT_STATE::HOLD;
		}
	}
		break;
	default:
		break;
	}
}

void Unit::MoveUnit(Vector2 _destination)
{
	m_movement->SetDestination(_destination);
	m_state = UNIT_STATE::MOVE;
}

void Unit::HoldUnit()
{
	m_state = UNIT_STATE::HOLD;
}

void Unit::OnCollisionStay(const Collision& _collision)
{
	RigidBody* rigid = GetComponent<RigidBody>();

	Transform* transform = GetComponent<Transform>();
	Transform* otherTransform = _collision.otherObject->GetComponent<Transform>();

	Vector2 position = transform->GetPosition();
	Vector2 otherPos = otherTransform->GetPosition();

	Vector2 direct = position - otherPos;
	direct.Normalize();

	float otherMass = rigid->GetMass();
	if (otherMass == FLT_MAX) // ������ ������Ʈ 
	{

	}
	else // �����̴� ������Ʈ
	{
		// ������ ���� ��ġ�� ������ ������ �������� �о�� 
		if (direct == Vector2::Zero)
		{
		}
		const float power = 100.f;
		Vector2 force = direct * power;

		rigid->AddForce(force);
	}


}
