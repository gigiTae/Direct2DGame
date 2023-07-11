#pragma once

#include "Component.h"

class GameObject;
struct AABB;
struct Collision;
class CircleCollider;
class BoxCollider;
struct Node;


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

	unsigned int GetID() const { return m_ID; }

	// 현재 충돌중인 충돌체 갯수 반환
	int GetCurrentCollison() { return m_currentCollision; }

	/// 충돌관련함수 
	virtual bool Collides(Vector2 _position) = 0;
	virtual bool Collides(CircleCollider* _circle) = 0;
	virtual bool Collides(BoxCollider* _box) = 0;

	bool Collides(Collider* _collider);

	/// Broadphase 관련

	virtual Vector2 GetMinPoint()const = 0;
	virtual Vector2 GetMaxPoint()const = 0;

	Node* GetNode(){ return m_node;}
	void SetNode(Node* _node)
	{ m_node = _node; }

private:
	// 충돌체의 아이디는 고유한 값을 가진다.
	const unsigned int m_ID;
	int m_currentCollision; // 현재 충돌중이 충돌체 갯수 

	// ObjectType 만큼 자신과 대응하는 노드가 있으므로
	// AABBTree에 해당하는 노드의 포인터를 type별로 가진다.
	Node* m_node;
};