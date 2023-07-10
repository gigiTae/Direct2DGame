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
	void OnCollisionEnter(const Collision& _collision);
	void OnCollisionExit(const Collision& _collision);
	void OnCollisionStay(const Collision& _collision);

	const unsigned int GetID() const { return m_ID; }

	int GetCurrentCollison() { return m_currentCollision; }

private:
	// 충돌체의 아이디는 고유한 값을 가진다.
	const unsigned int m_ID;
	int m_currentCollision; // 현재 충돌중이 충돌체 
};