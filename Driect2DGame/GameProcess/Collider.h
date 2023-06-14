#pragma once

struct Collision;
class InputManager;
class GameObject;

// 부모 충돌체 
class Collider abstract
{
public:
	virtual void FinalUpdate() abstract;
	virtual void DebugRender(D2DRenderer* _d2DRenderer) abstract;

public:
	virtual void OnCollisionEnter(const Collision& _collision, const InputManager* _inputManager) abstract;
	virtual void OnCollisionExit(const Collision& _collision, const InputManager* _inputManager) abstract;
	virtual void OnCollisionStay(const Collision& _collision, const InputManager* _inputManager) abstract;

	void SetOwner(GameObject* _owner) { m_owner = _owner; }
	GameObject* GetOwner() { return m_owner; }

	const unsigned int GetID() const{ return m_ID; }
	Collider();
	~Collider();
private:
	// 충돌체의 아이디는 고유한 값을 가진다.
	const unsigned int m_ID;
	// 충돌체를 소유한 오브젝트
	GameObject* m_owner;
};