#pragma once

#include "Component.h"

// 전방선언
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
/// 오브젝트의 기본형
/// 컴포넌트 구조를 가진다
/// 
/// </summary>
class GameObject
{

public:
	/// 생성자 단계에서 오브젝트의 이름을 결정
	GameObject(const string& _name, const ManagerSet* _managerSet);
	virtual ~GameObject();

public:
	/// 삭제예정인 오브젝트인지
	bool IsAlive();

	// 씬에게 오브젝트 삭제요청을 한다.
	void Destory(float _destoryTime = 0.f);
	const string& GetName() { return m_name; }

	/// !!경고!! 오브젝를 삭제하고 싶으면 Destory를 사용
	void SetObjectState(OBJECT_STATE _state) { m_state = _state; }
	OBJECT_STATE GetObjectState() { return m_state; }
	
	// 몇초후 삭제예정인지 반환
	float GetDestroyTime() { return m_destoryTime; }

public:
	void DestroyAllComponent();

	///  명시적 초기화
	void Initalize() {};
	void Finalize();

	/// 이벤트 함수 
	void FixedUpdate(float _fixedDeltaTime);
	void Update(float _deltaTime);
	void LateUpdate(float _deltaTime);
	void PreRender(D2DRenderer* _d2DRenderer);
	void Render(D2DRenderer* _d2DRenderer);
	void PostRender(D2DRenderer* _d2DRenderer);
	void DebugRender(D2DRenderer* _d2dRenderer);

	// 물리엔진 함수  
	void IntergrateForces(float _fixedDeltaTime);

public:
	/// 충돌 이벤트 함수
	void OnCollisionStay(const Collision& _collision, const InputManager* _inputManager) {};
	void OnCollisionEnter(const Collision& _collision, const InputManager* _inputManager) {};
	void OnCollisionExit(const Collision& _collision, const InputManager* _inputManager) {};

public:
	/// 자식 오브젝트 
	void AddChild(GameObject* _child);
	GameObject* GetChild(int _index);
	GameObject* GetChild(const string& _name);
	vector<GameObject*>& GetChildren();
	GameObject* GetParent();
	void SetParent(GameObject* _parent);

public: 
	/// 매니져 관련함수
	const ManagerSet* GetManagerSet()const { return m_managerSet; }
	const CameraManager* GetCameraManager()const;
	const PathManager* GetPathManager()const;
	const InputManager* GetInputManager()const;
	const TimeManager* GetTimeManager()const;
	const SceneManager* GetSceneManager()const;
	const UIManager* GetUIManager()const;
	const CollisionManager* GetCollisionManager()const;

	/// 마우스 입력 함수
	void OnMouse();
	void OnMouseUp();
	void OnMouseDown();
	void OnMouseClicked();

public:
	/// 컴포넌트 관련 함수 
	template <typename T>
	T* CreateComponent();

	template <typename T>
	T* GetComponent();

private:
	/// Component을 호출순서대로 정렬해서 보관
	std::multimap<int, Component*> m_components; 

private:
	OBJECT_STATE m_state;
	float m_destoryTime;
	const string m_name;

	// 매니져 포인터 집합
	const ManagerSet* m_managerSet;
};

// 여기 한번더 감싸서 Component의 메모리 관리를 게임오브젝트가 하면 편리하지 않을까?? real루다가
// 그래서 컴포너트의 생성이 실패하면 메모리에 추가하지 않는거지!
// Add-> 메모리를 할당을 외부에서 하는걸로 하고 Create 접두사는 객체가 직접 메모리를 관리한다의 의미로 사용하자

template <typename T>
T* GameObject::CreateComponent()
{
	// 이미 생성된 컴포넌트는 생성하지 않음
	if (nullptr != GetComponent<T>())
	{
		return nullptr;
	}

	T* tmp = new T();
	Component* component = dynamic_cast<Component*>(tmp);
	// dynamic_cast를 했는데 Component가 아닌경우에는 nullptr 이므로 다시 삭제
	if (component == nullptr)
	{
		delete tmp;
		return nullptr;
	}

	// 컴포넌트와 게임 오브젝트 연결
	component->SetGameObject(this);

	// 게임오브젝의 multpmap에 정보 컴포넌트 삽입
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

// 일반화(템플릿)말고 추상화로 구현하면, 외부에서 GetComponent등으로 받을 때, 캐스팅을 해서 써야한다
// => Transform* transform = dynamic_cast<Transform*>(GetComponent(COMPONENT_TPYE::TRANSFORM)); -> 이런식으로 템플리이 더 편리한듯 ? 