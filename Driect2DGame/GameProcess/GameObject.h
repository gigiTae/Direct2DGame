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

	/// �̺�Ʈ ���� �Լ� 
	virtual void Initalize() = 0;
	virtual void Finalize();
	virtual void FixedUpdate(float _fixedDeltaTime, InputManager* _inputManager) {};
	
	virtual void Update(float _deltaTime, InputManager* _inputManager) = 0;
	virtual void FinalUpdate(float _deltaTime);
	virtual void Render(D2DRenderer* _d2DRenderer) {};
	virtual void ComponentRender(D2DRenderer* _d2DRenderer);
	virtual void DebugRender(D2DRenderer* _d2dRenderer);
	
	// �������� �����Լ�  
	void IntergrateForces(float _fixedDeltaTime);

public:
	void SetDead() { m_ailve = false; }
	void SetAlive() { m_ailve = true; }
	bool IsAlive() { return m_ailve; }

	const string& GetName() { return m_name; }

private:
	// ���������� ������Ʈ���� Ȯ��
	bool m_ailve; 
	const string m_name;
public:
	void OnCollisionStay(const Collision& _collision, const InputManager* _inputManager) {};
	void OnCollisionEnter(const Collision& _collision, const InputManager* _inputManager) {};
	void OnCollisionExit(const Collision& _collision, const InputManager* _inputManager) {};

	/// ������Ʈ ���� �Լ� 
private:
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