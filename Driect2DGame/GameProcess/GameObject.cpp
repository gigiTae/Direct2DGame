#include "GameProcessPCH.h"
#include "GameObject.h"
#include"Transform.h"


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
}

void GameObject::CreateCircleCollider()
{
}

void GameObject::Render()
{
}
