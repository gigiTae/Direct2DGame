#include "GameProcessPCH.h"
#include "GameObject.h"
#include"Transform.h"
#include "BoxCollider.h"
#include "CircleCollider.h"


GameObject::GameObject(const wstring& _name)
	:m_name(_name)
	,m_ailve(true)
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
}

void GameObject::FinalUpdate(float _deltaTime)
{
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

void GameObject::Render(D2DRenderer* _d2DRenderer)
{
}

void GameObject::ComponentRender(D2DRenderer* _d2DRenderer)
{
	if (m_boxCollider != nullptr)
	{
		m_boxCollider->DebugRender(_d2DRenderer);
	}
	if (m_circleCollider != nullptr)
	{
		m_circleCollider->DebugRender(_d2DRenderer);
	}
}

void GameObject::Finalize()
{
	DestroyAllComponent();
}

