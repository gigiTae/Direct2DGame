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

	/// 이벤트 전용 함수 
	virtual void Initalize() = 0;
	virtual void Finalize();
	virtual void FixedUpdate(float _fixedDeltaTime, InputManager* _inputManager) {};
	
	virtual void Update(float _deltaTime, InputManager* _inputManager) = 0;
	virtual void FinalUpdate(float _deltaTime);
	virtual void Render(D2DRenderer* _d2DRenderer) {};
	virtual void ComponentRender(D2DRenderer* _d2DRenderer);
	virtual void DebugRender(D2DRenderer* _d2dRenderer);
	
	// 물리엔진 전용함수  
	void IntergrateForces(float _fixedDeltaTime);

public:
	void SetDead() { m_ailve = false; }
	void SetAlive() { m_ailve = true; }
	bool IsAlive() { return m_ailve; }

	const string& GetName() { return m_name; }

private:
	// 삭제예정인 오브젝트인지 확인
	bool m_ailve; 
	const string m_name;
public:
	void OnCollisionStay(const Collision& _collision, const InputManager* _inputManager) {};
	void OnCollisionEnter(const Collision& _collision, const InputManager* _inputManager) {};
	void OnCollisionExit(const Collision& _collision, const InputManager* _inputManager) {};

	/// 컴포넌트 관련 함수 
private:
	vector<Component*> m_components;

public:
	template <typename T>
	T* CreateComponent();

	template <typename T>
	T* GetComponent();

};



// 여기 한번더 감싸서 Component의 메모리 관리를 게임오브젝트가 하면 편리하지 않을까?? real루다가
// 그래서 컴포너트의 생성이 실패하면 메모리에 추가하지 않는거지!
// Add-> 메모리를 할당을 외부에서 하는걸로 하고 Create 접두사는 객체각 직접 메모리를 관리한다의 의미로 사용하자

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

	component->SetGameObject(this);
	m_components.push_back(component);

	return tmp;
}


template <typename T>
T* GameObject::GetComponent()
{
	// 찾으려는 컴포넌트의 정보를 바탕으로 벡터를 순회하면서 찾는다.
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

// 일반화(템플릿)말고 추상화로 구현하면, 외부에서 GetComponent등으로 받을 때, 캐스팅을 해서 써야한다
// => Transform* transform = dynamic_cast<Transform*>(GetComponent<Transform*>()); -> 이런식으로 템플리이 더 편리한듯 ? 