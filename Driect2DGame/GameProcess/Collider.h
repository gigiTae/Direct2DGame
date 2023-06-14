#pragma once

struct Collision;
class InputManager;
class GameObject;

// �θ� �浹ü 
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
	// �浹ü�� ���̵�� ������ ���� ������.
	const unsigned int m_ID;
	// �浹ü�� ������ ������Ʈ
	GameObject* m_owner;
};