#pragma once

class GameObject;
class InputManager;
class PathManager;
class SceneManager;
class TimeManager;
class UIManager;
class CollisionManager;

/// <summary>
/// 컴포넌의 기본적인 인터페이스이다
/// 
/// </summary>
class Component abstract
{
public:
	Component(CALL_ORDER _callOrder, string _name);
	virtual ~Component();

public:
	/// 기본적인 이벤트 함수
	virtual void FixedUpdate(float _fixedDeltaTime) {};
	virtual void Update(float _deltaTime) {};
	virtual void LateUpdate(float _deltaTime) {};

	/// 컴포넌트 랜러링 관련 함수 
	virtual void PreRender(D2DRenderer* _d2DRenderer) {};
	virtual void Render(D2DRenderer* _d2DRenderer) {};
	virtual void PostRender(D2DRenderer* _d2DRenderer) {};
	virtual void DebugRender(D2DRenderer* _d2DRendere) {};

public:
	/// 매니져 관련함수
	const PathManager* GetPathManager()const;
	const InputManager* GetInputManager()const;
	const TimeManager* GetTimeManager()const;
	const SceneManager* GetSceneManager()const;
	const UIManager* GetUIManager()const;
	const CollisionManager* GetCollisionManager()const;

public:
	void SetGameObject(GameObject* _gameObject) { m_gameObject = _gameObject; }
	GameObject* GetGameObject() { return m_gameObject; }
	const string& GetName() { return m_name; }
	CALL_ORDER GetCallOrder() { return m_callOrder; }

public:
	template <typename T>
	T* CreateComponent();

	template <typename T>
	T* GetComponent();

private:
	/// 컴포넌트 호출 순서
	const CALL_ORDER m_callOrder;
	/// 컴포넌트 클래스명
	const string m_name;
	GameObject* m_gameObject;
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

