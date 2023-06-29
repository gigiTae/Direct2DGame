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
	SetName(typeid(this).name());

}

void BoxCollider::OnCollisionEnter(const Collision& _collision, const InputManager* _inputManager)
{
	++m_currentCollision;
	assert(m_currentCollision >= 0);

	GetGameObject()->OnCollisionEnter(_collision, _inputManager);
}

void BoxCollider::OnCollisionExit(const Collision& _collision, const InputManager* _inputManager)
{
	--m_currentCollision;
	assert(m_currentCollision >= 0);

	GetGameObject()->OnCollisionExit(_collision, _inputManager);
}

void BoxCollider::OnCollisionStay(const Collision& _collision, const InputManager* _inputManager)
{
	GetGameObject()->OnCollisionStay(_collision, _inputManager);
}



BoxCollider::~BoxCollider()
{
}

void BoxCollider::Update()
{
	// ������Ʈ�� ��ġ�� ���� ���� �ݶ��̴� �̵�
	Vector2 ownerPosition = GetComponent<Transform>()->GetPosition();
	m_position = ownerPosition + m_offset;
	// ������Ʈ ȸ���� ���� �ݶ��̴��� ���� ȸ��
	if (m_isRotatable)
	{
		float ownerRotation = GetComponent<Transform>()->GetRotation();
		m_rotation = ownerRotation;
	}
}

void BoxCollider::DebugRender(D2DRenderer* _d2DRenderer)
{
	Vector2 leftTop;
	leftTop.x = m_position.x + m_scale.x * 0.5f;
	leftTop.y = m_position.y + m_scale.y * 0.5f;

	Vector2 rightBottom;
	rightBottom.x = m_position.x - m_scale.x * 0.5f;
	rightBottom.y = m_position.y - m_scale.y * 0.5f;

	Vector2 postion = GetComponent<Transform>()->GetPosition();

	if (m_isRotatable)
	{
		_d2DRenderer->SetTransform(-m_rotation, postion);
	}

	// �浹��Ȳ�� ���� ������
	if (m_currentCollision == 0)
	{ 
		_d2DRenderer->DrawRectangle(leftTop, rightBottom,D2D1::ColorF::LightGreen);
	}
	else
	{
		_d2DRenderer->DrawRectangle(leftTop, rightBottom, D2D1::ColorF::Red);
	}

	_d2DRenderer->SetTransform(0.f, Vector2::Zero);
}

