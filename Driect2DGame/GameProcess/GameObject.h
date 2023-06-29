#pragma once

#include "Component.h"

// ���漱��
class Transform;
class BoxCollider;
class CircleCollider;
class InputManager;
class Collider;
class RigidBody;

struct Collision;

/// <summary>
/// ������Ʈ�� �⺻��
/// ������Ʈ ������������ �����ϰ� ������Ʈ�� �����غ���!
/// 
/// </summary>
class GameObject
{

public:
	// ������ �ܰ迡�� ������Ʈ�� �̸��� ����
	GameObject(const string& _name);
	virtual ~GameObject();

public:
	void DestroyAllComponent();

	/// �̺�Ʈ �Լ� 
	void Initalize() {};
	void Finalize();
	void FixedUpdate(float _fixedDeltaTime, InputManager* _inputManager);

	void Update(float _deltaTime, InputManager* _inputManager);
	void FinalUpdate(float _deltaTime);
	void PreRender(D2DRenderer* _d2DRenderer);
	void Render(D2DRenderer* _d2DRenderer);
	void PostRender(D2DRenderer* _d2DRenderer);
	void DebugRender(D2DRenderer* _d2dRenderer);

	// �������� �Լ�  
	void IntergrateForces(float _fixedDeltaTime);

public:
	/// �浹 �̺�Ʈ �Լ�
	void OnCollisionStay(const Collision& _collision, const InputManager* _inputManager) {};
	void OnCollisionEnter(const Collision& _collision, const InputManager* _inputManager) {};
	void OnCollisionExit(const Collision& _collision, const InputManager* _inputManager) {};

public:
	void SetAlive(bool _isAlive) { m_ailve = _isAlive; }
	bool IsAlive() { return m_ailve; }
	const string& GetName() { return m_name; }

private:
	// ���������� ������Ʈ���� Ȯ��
	bool m_ailve;
	const string m_name;

public:
	/// �ڽ� ������Ʈ 
	void AddChild(GameObject* _child);
	GameObject* GetChild(int _index);
	const vector<GameObject*>& GetChildren();
	GameObject* GetParent();
	void SetParent(GameObject* _parent);

private:
	/// ������Ʈ ���� �Լ� 
	/// ������Ʈ�� ���Ͱ� �ƴ� ���ĵ� ���·� ������ ������ ȣ������� ���Ҽ� ����������? 
	vector<Component*> m_components;

public:
	template <typename T>
	T* CreateComponent();

	template <typename T>
	T* GetComponent();

};

// ���� �ѹ��� ���μ� Component�� �޸� ������ ���ӿ�����Ʈ�� �ϸ� ������ ������?? real��ٰ�
// �׷��� ������Ʈ�� ������ �����ϸ� �޸𸮿� �߰����� �ʴ°���!
// Add-> �޸𸮸� �Ҵ��� �ܺο��� �ϴ°ɷ� �ϰ� Create ���λ�� ��ü�� ���� �޸𸮸� �����Ѵ��� �ǹ̷� �������

template <typename T>
T* GameObject::CreateComponent()
{
	// �̹� ������ ������Ʈ�� �������� ����
	if (nullptr != GetComponent<T>())
	{
		return nullptr;
	}

	T* tmp = new T();
	Component* component = dynamic_cast<Component*>(tmp);
	// dynamic_cast�� �ߴµ� Component�� �ƴѰ�쿡�� nullptr �̹Ƿ� �ٽ� ����
	if (component == nullptr)
	{
		delete tmp;
		return nullptr;
	}

	component->SetGameObject(this);
	m_components.push_back(component);

	return tmp;
}

template <typename T>
T* GameObject::GetComponent()
{
	// ã������ ������Ʈ�� ������ �������� ���͸� ��ȸ�ϸ鼭 ã�´�.
	// 
	const type_info& _infoT = typeid(T);

	for (Component* component : m_components)
	{
		const type_info& _info = typeid(*component);

		if (_info.name() == _infoT.name())
		{
			return dynamic_cast<T*>(component);
		}
	}

	return nullptr;
}

// �Ϲ�ȭ(���ø�)���� �߻�ȭ�� �����ϸ�, �ܺο��� GetComponent������ ���� ��, ĳ������ �ؼ� ����Ѵ�
// => Transform* transform = dynamic_cast<Transform*>(GetComponent<Transform*>()); -> �̷������� ���ø��� �� ���ѵ� ? 