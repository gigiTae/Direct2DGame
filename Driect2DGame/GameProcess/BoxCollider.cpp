#include "GameProcessPCH.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Transform.h"

BoxCollider::BoxCollider()
	:m_offset{}
	, m_currentCollision(0)
	, m_position{}
	, m_rotation(0.f)
	, m_scale{}
	, m_isRotatable(false)
	, m_active(false)
{
}

void BoxCollider::OnCollisionEnter(const Collision& _collision, const InputManager* _inputManager)
{
	++m_currentCollision;
	assert(m_currentCollision >= 0);

	_collision.otherObject->OnCollisionEnter(_collision, _inputManager);
}

void BoxCollider::OnCollisionExit(const Collision& _collision, const InputManager* _inputManager)
{
	--m_currentCollision;
	assert(m_currentCollision >= 0);

	_collision.otherObject->OnCollisionExit(_collision, _inputManager);
}

void BoxCollider::OnCollisionStay(const Collision& _collision, const InputManager* _inputManager)
{
	_collision.otherObject->OnCollisionStay(_collision, _inputManager);
}



BoxCollider::~BoxCollider()
{
}

void BoxCollider::FinalUpdate()
{
	// 오브젝트의 위치에 따라서 같이 콜라이더 이동
	Vector2 ownerPosition = GetOwner()->GetTransform()->GetPosition();
 	m_position = ownerPosition + m_offset;
}

void BoxCollider::DebugRender(D2DRenderer* _d2DRenderer)
{
	Vector2 leftTop;
	leftTop.x = m_position.x + m_scale.x * 0.5f;
	leftTop.y = m_position.y + m_scale.y * 0.5f;

	Vector2 rightBottom;
	rightBottom.x = m_position.x - m_scale.x * 0.5f;
	rightBottom.y = m_position.y - m_scale.y * 0.5f;

	// 충돌상황에 따라서 랜더링
	if (m_currentCollision == 0)
	{
		_d2DRenderer->DrawRectangle(leftTop, rightBottom, RGB(0, 255, 0));
	}
	else
	{
		_d2DRenderer->DrawRectangle(leftTop, rightBottom, RGB(255, 0, 0));
	}
}

