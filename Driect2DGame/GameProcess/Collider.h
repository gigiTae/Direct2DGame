#pragma once

#include "Component.h"

struct Collision;
class InputManager;
class GameObject;

// 부모 충돌체 
class Collider abstract
	:public Component
{
public:
	Collider(string _name);
	~Collider();

public:
	virtual void OnCollisionEnter(const Collision& _collision, const InputManager* _inputManager) abstract;
	virtual void OnCollisionExit(const Collision& _collision, const InputManager* _inputManager) abstract;
	virtual void OnCollisionStay(const Collision& _collision, const InputManager* _inputManager) abstract;

	const unsigned int GetID() const{ return m_ID; }

private:
	// 충돌체의 아이디는 고유한 값을 가진다.
	const unsigned int m_ID;
};