#include "GameProcessPCH.h"
#include "GameObject.h"
#include"Transform.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "RigidBody.h"
#include "NamingManager.h"
#include "MonoBehaviour.h"

GameObject::GameObject(const string& _name)
	:m_name(NamingManager::GetInstance()->GenerateName(_name))
	,m_state(OBJECT_STATE::ALIVE)
	,m_destoryTime(0.f)
{}

GameObject::~GameObject()
{}

bool GameObject::IsAlive()
{
	/// ���� ������ ������Ʈ�� ���� �������� �ʾ����Ƿ� true�� ��ȯ�Ѵ�.
	if (m_state != OBJECT_STATE::DESTORY)
		return true;

	return false;
}

void GameObject::Destory(float _destoryTime /*= 0.f*/)
{
	/// ���� �ð����Ŀ� ���� && ���� ���� ������û�� �޴´�.
	if (m_state == OBJECT_STATE::ALIVE)
	{
		m_state = OBJECT_STATE::TO_BE_DESTORYED;
		m_destoryTime = _destoryTime;
	}
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

void GameObject::OnMouse()
{
	for (auto& iter : m_components)
	{
		MonoBehaviour* monoBehaviour = dynamic_cast<MonoBehaviour*>(iter.second);
		if (monoBehaviour != nullptr)
		{
			monoBehaviour->OnMouse();
		}
	}
}

void GameObject::OnMouseUp()
{
	for (auto& iter : m_components)
	{
		MonoBehaviour* monoBehaviour = dynamic_cast<MonoBehaviour*>(iter.second);
		if (monoBehaviour != nullptr)
		{
			monoBehaviour->OnMouseUp();
		}
	}
}

void GameObject::OnMouseDown()
{
	for (auto& iter : m_components)
	{
		MonoBehaviour* monoBehaviour = dynamic_cast<MonoBehaviour*>(iter.second);
		if (monoBehaviour != nullptr)
		{
			monoBehaviour->OnMouseDown();
		}
	}
}

void GameObject::OnMouseClicked()
{
	for (auto& iter : m_components)
	{
		MonoBehaviour* monoBehaviour = dynamic_cast<MonoBehaviour*>(iter.second);
		if (monoBehaviour != nullptr)
		{
			monoBehaviour->OnMouseClicked();
		}
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

GameObject* GameObject::GetChild(const string& _name)
{
	Transform* transform = GetComponent<Transform>();
	assert(transform);

	return transform->GetChild(_name);
}

vector<GameObject*>& GameObject::GetChildren()
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
	/// ������Ʈ�� ��ȸ�ϸ鼭 ���ĵ� ������ ���� Update�� ȣ���Ѵ�.
	for (auto& iter : m_components)
	{
		if (iter.second != nullptr)
		{
			iter.second->Update(_deltaTime, _inputManager);
		}
	}

	/// ���� ������ ������Ʈ ó�� 
	if (m_state == OBJECT_STATE::TO_BE_DESTORYED)
	{
		m_destoryTime -= _deltaTime;
		if (m_destoryTime <= 0.f)
		{
			m_destoryTime = 0.f;
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
	/// �ڽ� ������Ʈ, �θ������Ʈ ����ó�� 
	vector<GameObject*>& children = GetChildren();
	for (auto child : children)
	{
		child->SetParent(nullptr);
	}

	GameObject* parent = GetParent();

	if (parent != nullptr)
	{
		vector<GameObject*>& sibling = parent->GetChildren();

		for (auto iter = sibling.begin(); iter != sibling.end();)
		{
			if ((*iter) == this)
			{
				iter = sibling.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	DestroyAllComponent();
}
