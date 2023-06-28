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
	/// 컴포넌트를 순회하면서 UserScript들만 Update를 호출한다.
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
	/// 컴포넌트를 순회하면서 UserScript들만 Render 함수를 호출한다.
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
	/// 업데이트 순서가 중요하다

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
	// 충돌체 디버그용 렌더링
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
	// 디버그용도의 오브젝트 정보

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

