#include "GameProcessPCH.h"
#include "GameObject.h"
#include"Transform.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "RigidBody.h"
#include "NameGenerator.h"


GameObject::GameObject(const wstring& _name)
	:m_name(NameGenerator::GetInstance()->GenerateName(_name))
	,m_ailve(true)
	,m_rigidBody(nullptr)
	,m_boxCollider(nullptr)
	,m_circleCollider(nullptr)
	,m_transform(nullptr)
{
}

GameObject::~GameObject()
{
}

void GameObject::CreateTransform(const Vector2& _position, const Vector2& _scale, float _rotation)
{
	m_transform = new Transform();
	m_transform->SetPosition(_position);
	m_transform->SetScale(_scale);
	m_transform->SetRotation(_rotation);
}

void GameObject::CreateBoxCollider()
{
	m_boxCollider = new BoxCollider(); 
	m_boxCollider->SetOwner(this);
	m_boxCollider->SetActive(true);
}

void GameObject::CreateCircleCollider()
{
	m_circleCollider = new CircleCollider();
	m_circleCollider->SetOwner(this);
	m_circleCollider->SetActive(true);
}

void GameObject::CreateRigidBody(float _mass, Vector2 _scale)
{
	m_rigidBody = new RigidBody(this, _mass, _scale);
}

void GameObject::DestroyAllComponent()
{

	if (m_transform != nullptr)
	{
		delete m_transform;
		m_transform = nullptr;
	}
	if (m_boxCollider != nullptr)
	{
		delete m_boxCollider;
		m_boxCollider = nullptr;
	}
	if (m_circleCollider != nullptr)
	{
		delete m_circleCollider;
		m_circleCollider = nullptr;
	}
	if (m_rigidBody != nullptr)
	{
		delete m_rigidBody;
		m_rigidBody = nullptr;
	}
}

void GameObject::IntergrateForces(float _fixedDeltaTime)
{
	if (m_rigidBody != nullptr)
		m_rigidBody->IntegrateForces(_fixedDeltaTime);
}

void GameObject::FinalUpdate(float _deltaTime)
{
	if (m_rigidBody != nullptr)
	{
		m_rigidBody->FinalUpdate(_deltaTime);
	}

	if (m_transform != nullptr)
	{
		m_transform->FinalUpdate();
	}

	if (m_boxCollider != nullptr)
	{
		m_boxCollider->FinalUpdate();
	}
	if (m_circleCollider != nullptr)
	{
		m_circleCollider->FinalUpdate();
	}
}

void GameObject::DebugRender(D2DRenderer* _d2dRenderer)
{
	// 충돌체 디버그용 렌더링
	if (m_boxCollider != nullptr)
	{
		m_boxCollider->DebugRender(_d2dRenderer);
	}
	if (m_circleCollider != nullptr)
	{
		m_circleCollider->DebugRender(_d2dRenderer);
	}
	// 디버그용도의 오브젝트 정보
	if (m_transform != nullptr)
	{
		m_transform->DebugRender(_d2dRenderer);
	}
}

void GameObject::ComponentRender(D2DRenderer* _d2DRenderer)
{
	// 애니메이션 or 테스트 or 도형 그리기
}

void GameObject::Finalize()
{
	DestroyAllComponent();
}

