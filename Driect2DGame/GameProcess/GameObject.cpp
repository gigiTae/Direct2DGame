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
	,m_ailve(true)
{}

GameObject::~GameObject()
{}

void GameObject::Destory(float _destoryTime /*= 0.f*/)
{

}

void GameObject::DestroyAllComponent()
{
	for (auto& iter : m_components)
	{
		if (iter.second != nullptr)
		{
			delete iter.second;
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

void GameObject::AddChild(GameObject* _child)
{
	Transform* transform = GetComponent<Transform>();
	assert(transform);
	transform->AddChild(_child);
}

GameObject* GameObject::GetChild(int _index)
{
	Transform* transform = GetComponent<Transform>();
	assert(transform);

	return transform->GetChild(_index);
}

const vector<GameObject*>& GameObject::GetChildren()
{
	Transform* transform = GetComponent<Transform>();
	assert(transform);

	return transform->GetChildren();
}

GameObject* GameObject::GetParent()
{
	Transform* transform = GetComponent<Transform>();
	assert(transform);

	return transform->GetParent();
}

void GameObject::SetParent(GameObject* _parent)
{
	Transform* transform = GetComponent<Transform>();
	assert(transform);

	transform->SetParent(_parent);
}


void GameObject::FixedUpdate(float _fixedDeltaTime, InputManager* _inputManager)
{
	for (auto& iter : m_components)
	{
		if (iter.second != nullptr)
		{
			iter.second->FixedUpdate(_fixedDeltaTime, _inputManager);
		}
	}
}

void GameObject::Update(float _deltaTime, InputManager* _inputManager)
{
	/// 컴포넌트를 순회하면서 정렬된 순서에 따라서 Update를 호출한다.
	for (auto& iter : m_components)
	{
		if (iter.second != nullptr)
		{
			iter.second->Update(_deltaTime, _inputManager);
		}
	}
}

void GameObject::LateUpdate(float _deltaTime, InputManager* _inputManager)
{
	for (auto& iter : m_components)
	{
		if (iter.second != nullptr)
		{
			iter.second->LateUpdate(_deltaTime, _inputManager);
		}
	}
}

void GameObject::PreRender(D2DRenderer* _d2DRenderer)
{
	for (auto& iter : m_components)
	{
		if (iter.second != nullptr)
		{
			iter.second->PreRender(_d2DRenderer);
		}
	}
}

void GameObject::Render(D2DRenderer* _d2DRenderer)
{
	for (auto& iter : m_components)
	{
		if (iter.second != nullptr)
		{
			iter.second->Render(_d2DRenderer);
		}
	}
}

void GameObject::PostRender(D2DRenderer* _d2DRenderer)
{
	for (auto& iter : m_components)
	{
		if (iter.second != nullptr)
		{
			iter.second->PostRender(_d2DRenderer);
		}
	}
}

void GameObject::DebugRender(D2DRenderer* _d2dRenderer)
{
	for (auto& iter : m_components)
	{
		if (iter.second != nullptr)
		{
			iter.second->DebugRender(_d2dRenderer);
		}
	}
}

void GameObject::Finalize()
{
	DestroyAllComponent();
}
