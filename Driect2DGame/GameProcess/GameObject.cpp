#include "GameProcessPCH.h"
#include "GameObject.h"
#include"Transform.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "RigidBody.h"
#include "NameGenerator.h"

GameObject::GameObject(const string& _name)
	:m_name(NameGenerator::GetInstance()->GenerateName(_name))
	,m_ailve(true)
{
}

GameObject::~GameObject()
{
}

void GameObject::DestroyAllComponent()
{
	for (int i = 0; i < static_cast<int>(m_components.size()); ++i)
	{
		if (m_components[i] != nullptr)
		{
			delete m_components[i];
		}
	}
}

void GameObject::IntergrateForces(float _fixedDeltaTime)
{
	RigidBody* rigidBody = GetComponent<RigidBody>();
	if (rigidBody != nullptr)
	{
		rigidBody->IntegrateForces(_fixedDeltaTime);
	}
}

void GameObject::FinalUpdate(float _deltaTime)
{
	/// FinalUpdate�� ������ ��Ȯ�ϰ� �ϱ� ���ؼ� vector�� �ݺ����� ������� �ʴ´�.

	RigidBody* rigiBody = GetComponent<RigidBody>();
	if (rigiBody != nullptr)
	{
		rigiBody->Update(_deltaTime);
	}

	Transform* transform = GetComponent<Transform>();
	if (transform != nullptr)
	{
		transform->Update();
	}

	BoxCollider* boxCollider = GetComponent<BoxCollider>();
	if (boxCollider != nullptr)
	{
		boxCollider->Update();
	}

	CircleCollider* circleCollider = GetComponent<CircleCollider>();
	if (circleCollider != nullptr)
	{
		circleCollider->Update();
	}
}

void GameObject::DebugRender(D2DRenderer* _d2dRenderer)
{
	// �浹ü ����׿� ������
	BoxCollider* boxCollider = GetComponent<BoxCollider>();
	if (boxCollider != nullptr)
	{
		boxCollider->DebugRender(_d2dRenderer);
	}
	CircleCollider* circleCollider = GetComponent<CircleCollider>();
	if (circleCollider != nullptr)
	{
		circleCollider->DebugRender(_d2dRenderer);
	}
	// ����׿뵵�� ������Ʈ ����

	Transform* transform = GetComponent<Transform>();
	if (transform != nullptr)
	{
		transform->DebugRender(_d2dRenderer);
	}
}

void GameObject::ComponentRender(D2DRenderer* _d2DRenderer)
{
	// �ִϸ��̼� or �׽�Ʈ or ���� �׸���
}

void GameObject::Finalize()
{
	DestroyAllComponent();
}

