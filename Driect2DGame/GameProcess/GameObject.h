#pragma once

#include "Component.h"

// 전방선언
class Transform;
class BoxCollider;
class CircleCollider;
class InputManager;
class Collider;
class RigidBody;

struct Collision;

/// <summary>
/// 오브젝트의 기본형
/// 컴포넌트 구조를가지고 유연하게 오브젝트를 설계해보자!
/// 
/// </summary>
class GameObject
{

public:
	// 생성자 단계에서 오브젝트의 이름을 결정
	GameObject(const string& _name);
	virtual ~GameObject();

public:
	void DestroyAllComponent();

	/// 이벤트 함수 
	void Initalize() {};
	void Finalize();

	void FixedUpdate(float _fixedDeltaTime, InputManager* _inputManager);
	void Update(float _deltaTime, InputManager* _inputManager);
	void LateUpdate(float _deltaTime, InputManager* _inputManager);
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
	void SetAlive(bool _isAlive) { m_ailve = _isAlive; }
	bool IsAlive() { return m_ailve; }
	const string& GetName() { return m_name; }

private:
	// 삭제예정인 오브젝트인지 확인
	bool m_ailve;
	const string m_name;

public:
	/// 자식 오브젝트 
	void AddChild(GameObject* _child);
	GameObject* GetChild(int _index);
	const vector<GameObject*>& GetChildren();
	GameObject* GetParent();
	void SetParent(GameObject* _parent);

private:
	/// 컴포넌트 관련 함수 
	/// 컴포넌트를 벡터가 아닌 정렬된 형태로 가지고 있으면 호출순서를 정할수 있지않을까? 
	/// qriorty queue는 iterator 지원 x 그리고 multimap인 이유? 같은 순서를 가지는 컴포넌트는 중복으로 보관해야하므로
	/// 일반 map의 경우에는 같은 key값의 중복을 허용하지 않는다.
	std::multimap<int, Component*> m_components; 

public:
	template <typename T>
	T* CreateComponent();

	template <typename T>
	T* GetComponent();

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
	// 찾으려는 컴포넌트의 정보를 바탕으로 맵을 순회하면서 찾는다.
	const type_info& _info = typeid(T*);

	for (auto iter : m_components)
	{
		Component* component = iter.second;

		if (_info.name() == component->GetName())
		{
			return dynamic_cast<T*>(component);
		}
	}

	return nullptr;
}

// 일반화(템플릿)말고 추상화로 구현하면, 외부에서 GetComponent등으로 받을 때, 캐스팅을 해서 써야한다
// => Transform* transform = dynamic_cast<Transform*>(GetComponent<Transform*>()); -> 이런식으로 템플리이 더 편리한듯 ? 