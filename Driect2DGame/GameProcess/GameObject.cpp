#include "GameProcessPCH.h"
#include "GameObject.h"
#include"Transform.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "RigidBody.h"
#include "NameGenerator.h"
#include "MonoBehaviour.h"

GameObject::GameObject(const string& _name)
	:m_name(NameGenerator::GetInstance()->GenerateName(_name))
	,m_parent(nullptr)
	,m_children{}
	,m_ailve(true)
{}

GameObject::~GameObject()
{}

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

void GameObject::Update(float _deltaTime, InputManager* _inputManager)
{
	/// ������Ʈ�� ��ȸ�ϸ鼭 UserScript�鸸 Update�� ȣ���Ѵ�.
	for (auto component : m_components)
	{
		MonoBehaviour* userScript = dynamic_cast<MonoBehaviour*> (component);
		if (userScript != nullptr)
		{
			userScript->Update(_deltaTime, _inputManager);
		}
	}
}

void GameObject::PreRender(D2DRenderer* _d2DRenderer)
{
	for (auto component : m_components)
	{
		MonoBehaviour* userScript = dynamic_cast<MonoBehaviour*> (component);
		if (userScript != nullptr)
		{
			userScript->PreRender(_d2DRenderer);
		}
	}
}

void GameObject::Render(D2DRenderer* _d2DRenderer)
{
	/// ������Ʈ�� ��ȸ�ϸ鼭 UserScript�鸸 Render �Լ��� ȣ���Ѵ�.
	for (auto component : m_components)
	{
		MonoBehaviour* userScript = dynamic_cast<MonoBehaviour*> (component);
		if (userScript != nullptr)
		{
			userScript->Render(_d2DRenderer);
		}
	}
}

void GameObject::PostRender(D2DRenderer* _d2DRenderer)
{
	for (auto component : m_components)
	{
		MonoBehaviour* userScript = dynamic_cast<MonoBehaviour*> (component);
		if (userScript != nullptr)
		{
			userScript->PostRender(_d2DRenderer);
		}
	}
}

void GameObject::FinalUpdate(float _deltaTime)
{
	/// ������Ʈ ������ �߿��ϴ�

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

void GameObject::Finalize()
{
	DestroyAllComponent();
}

