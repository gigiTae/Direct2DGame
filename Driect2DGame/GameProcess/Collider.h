#pragma once

#include "Component.h"

struct Collision;
class InputManager;
class GameObject;

// �θ� �浹ü 
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
	// �浹ü�� ���̵�� ������ ���� ������.
	const unsigned int m_ID;
};