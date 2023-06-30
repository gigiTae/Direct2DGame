#pragma once

class GameObject;
class InputManager;

class Component abstract
{
public:
	Component(CALL_ORDER _callOrder, string _name);
	virtual ~Component();

public:
	/// �⺻���� �̺�Ʈ �Լ�
	virtual void FixedUpdate(float _fixedDeltaTime, InputManager* _inputManager) {};
	virtual void Update(float _deltaTime, InputManager* _inputManager) {};
	virtual void LateUpdate(float _deltaTime, InputManager* _inputManager) {};

	/// ������Ʈ ������ ���� �Լ� 
	virtual void PreRender(D2DRenderer* _d2DRenderer) {};
	virtual void Render(D2DRenderer* _d2DRenderer) {};
	virtual void PostRender(D2DRenderer* _d2DRenderer) {};
	virtual void DebugRender(D2DRenderer* _d2DRendere) {};

public:
	void SetGameObject(GameObject* _gameObject) { m_gameObject = _gameObject; }
	GameObject* GetGameObject() { return m_gameObject; }
	const string& GetName() { return m_name; }
	CALL_ORDER GetCallOrder() { return m_callOrder; }

private:
	/// ������Ʈ ȣ�� ����
	const CALL_ORDER m_callOrder;
	/// ������Ʈ Ŭ������
	const string m_name;
	GameObject* m_gameObject;
public:
	template <typename T>
	T* CreateComponent();

	template <typename T>
	T* GetComponent();
};

 
template <typename T>
T* Component::CreateComponent()
{
	if (m_gameObject != nullptr)
	{
		return m_gameObject->template CreateComponent<T>();
	}
	return nullptr;
}

template <typename T>
T* Component::GetComponent()
{
	if (m_gameObject != nullptr)
	{
		return m_gameObject->template GetComponent<T>();
	}

	return nullptr;
}