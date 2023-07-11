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
	if (false)//otherMass == FLT_MAX) // 고정된 오브젝트 
	{
		float otherRadius = _collision.otherObject->GetComponent<CircleCollider>()->GetRadius();
		float radius = GetComponent<CircleCollider>()->GetRadius();
		
		Vector2 pushDistance = direct * (otherRadius + radius - (position - otherPos).Length());

		transform->AddPosition(pushDistance);
	}

	else // 움직이느 오브젝트
	{
		//return;
		// 완전히 같은 위치에 있으면 랜던함 방향으로 밀어내기 
		if (direct == Vector2::Zero)
		{
		}
		constexpr float power = 500.f;
		Vector2 force = direct * power;

		rigid->AddForce(force);
	}


}
