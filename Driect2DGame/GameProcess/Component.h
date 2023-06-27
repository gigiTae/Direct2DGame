#pragma once

class GameObject;

class Component abstract
{
public:
	Component();
	virtual ~Component();

	void SetGameObject(GameObject* _gameObject) { m_gameObject = _gameObject; }
	GameObject* GetGameObject() { return m_gameObject; }
	string GetName() { return m_name; }
private:
	const std::string m_name;
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