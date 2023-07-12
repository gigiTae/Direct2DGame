#pragma once

#include "Component.h"

// ���漱��
class ManagerSet;
class InputManager;
class PathManager;
class SceneManager;
class TimeManager;
class UIManager;
class CollisionManager;
class CameraManager;
struct Collision;

/// <summary>
/// ������Ʈ�� �⺻��
/// ������Ʈ ������ ������
/// 
/// </summary>
class GameObject
{

public:
	/// ������ �ܰ迡�� ������Ʈ�� �̸��� ����
	GameObject(const string& _name, const ManagerSet* _managerSet, OBJECT_TYPE _type);
	virtual ~GameObject();

public:
	/// ���������� ������Ʈ����
	bool IsAlive();

	// ������ ������Ʈ ������û�� �Ѵ�.
	void Destory(float _destoryTime = 0.f);
	const string& GetName() { return m_name; }

	/// !!���!! �������� �����ϰ� ������ Destory�� ���
	void SetObjectState(OBJECT_STATE _state) { m_state = _state; }
	OBJECT_STATE GetObjectState() { return m_state; }
	OBJECT_TYPE GetObjectType() { return m_type; }

	// ������ ������������ ��ȯ
	float GetDestroyTime() { return m_destoryTime; }

public:
	void DestroyAllComponent();

	///  ����� �ʱ�ȭ
	void Initalize() {};
	void Finalize();

	/// �̺�Ʈ �Լ� 
	void FixedUpdate(float _fixedDeltaTime);
	void Update(float _deltaTime);
	void LateUpdate(float _deltaTime);
	void PreRender(D2DRenderer* _d2DRenderer);
	void Render(D2DRenderer* _d2DRenderer);
	void PostRender(D2DRenderer* _d2DRenderer);
	void DebugRender(D2DRenderer* _d2dRenderer);

	// �������� �Լ�  
	void IntergrateForces(float _fixedDeltaTime);

public:
	/// ī�޶� ������ �޴� ������Ʈ���� 
	bool IsCameraAffected() { return m_cameraAffected; }
	void SetCameraAffected(bool _isAffected) { m_cameraAffected = _isAffected; }

public:
	/// �ڽ� ������Ʈ 
	void AddChild(GameObject* _child);
	GameObject* GetChild(int _index);
	GameObject* GetChild(const string& _name);
	vector<GameObject*>& GetChildren();
	GameObject* GetParent();
	void SetParent(GameObject* _parent);

public: 
	/// �Ŵ��� �����Լ�
	const ManagerSet* GetManagerSet()const { return m_managerSet; }
	const CameraManager* GetCameraManager()const;
	const PathManager* GetPathManager()const;
	const InputManager* GetInputManager()const;
	const TimeManager* GetTimeManager()const;
	const SceneManager* GetSceneManager()const;
	const UIManager* GetUIManager()const;
	const CollisionManager* GetCollisionManager()const;

	/// ���콺 �Է� �Լ�
	void OnMouse();
	void OnMouseUp();
	void OnMouseDown();
	void OnMouseClicked();

	/// �浹 �����Լ�
	void OnCollisionEnter(const Collision& _collision);
	void OnCollisionExit(const Collision& _collision);
	void OnCollisionStay(const Collision& _collision);

public:
	/// ������Ʈ ���� �Լ� 
	template <typename T>
	T* CreateComponent();

	template <typename T>
	T* GetComponent();

private:
	/// Component�� ȣ�������� �����ؼ� ����
	std::multimap<int, Component*> m_components; 

private:
	OBJECT_STATE m_state;
	OBJECT_TYPE m_type;

	float m_destoryTime;
	const string m_name;

	// ī�޶� ������ �޴� ������Ʈ���� 
	bool m_cameraAffected;
	// �Ŵ��� ������ ����
	const ManagerSet* m_managerSet;
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

	// ������Ʈ�� ���� ������Ʈ ����
	component->SetGameObject(this);

	// ���ӿ������� multpmap�� ���� ������Ʈ ����
	int callOreder = static_cast<int>(component->GetCallOrder());
	m_components.insert(make_pair(callOreder, component));

	return tmp;
}

template <typename T>
T* GameObject::GetComponent()
{
	for (auto& iter : m_components)
	{
		T* component = dynamic_cast<T*>(iter.second);
		if (component != nullptr)
		{
			return component;
		}
	}

	return nullptr;
}

// �Ϲ�ȭ(���ø�)���� �߻�ȭ�� �����ϸ�, �ܺο��� GetComponent������ ���� ��, ĳ������ �ؼ� ����Ѵ�
// => Transform* transform = dynamic_cast<Transform*>(GetComponent(COMPONENT_TPYE::TRANSFORM)); -> �̷������� ���ø��� �� ���ѵ� ? 