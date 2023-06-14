#pragma once


// 전방선언
class Transform;
class BoxCollider;
class CircleCollider;
class InputManager;
class Collider;
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
	GameObject(const wstring& _name);
	virtual ~GameObject();

public:
	void CreateTransform(const Vector2& _position, const Vector2& _scale, float _rotation = 0.f);
	void CreateBoxCollider();
	void CreateCircleCollider();

	void DestroyAllComponent();

	Transform* GetTransform() { return m_transform; }
	BoxCollider* GetBoxCollider() { return m_boxCollider; }
	CircleCollider* GetCircleCollider() { return m_circleCollider; }

	virtual void Initalize() = 0;
	virtual void Update(float _deltaTime, InputManager* inputManager) = 0;
	virtual void FinalUpdate(float _deltaTime);
	virtual void Render(D2DRenderer* _d2DRenderer);
	virtual void ComponentRender(D2DRenderer* _d2DRenderer);
	virtual void Finalize();

public:
	void SetDead() { m_ailve = false; }
	void SetAlive() { m_ailve = true; }

	const wstring& GetName() { return m_name; }

	// 삭제예정인 오브젝트인지 확인
	bool IsAlive() { return m_ailve; }

private:
	Transform* m_transform;
	BoxCollider* m_boxCollider;
	CircleCollider* m_circleCollider;
	bool m_ailve; 

	const wstring m_name;
public:
	void OnCollisionStay(const Collision& _collision, const InputManager* _inputManager) {};
	void OnCollisionEnter(const Collision& _collision, const InputManager* _inputManager) {};
	void OnCollisionExit(const Collision& _collision, const InputManager* _inputManager) {};
};

