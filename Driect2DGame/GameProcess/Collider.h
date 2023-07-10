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
	void OnCollisionEnter(const Collision& _collision);
	void OnCollisionExit(const Collision& _collision);
	void OnCollisionStay(const Collision& _collision);

	const unsigned int GetID() const { return m_ID; }

	int GetCurrentCollison() { return m_currentCollision; }

private:
	// �浹ü�� ���̵�� ������ ���� ������.
	const unsigned int m_ID;
	int m_currentCollision; // ���� �浹���� �浹ü 
};