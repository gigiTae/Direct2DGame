#pragma once

#include "Component.h"

class GameObject;
struct AABB;
struct Collision;
class CircleCollider;
class BoxCollider;
struct Node;

/// <summary>
/// �浹ü �������̽�
/// </summary>
class Collider abstract
	:public Component
{
public:
	Collider(string _name, COLLIDER_TYPE _type);
	~Collider();

public:
	void OnCollisionEnter(const Collision& _collision);
	void OnCollisionExit(const Collision& _collision);
	void OnCollisionStay(const Collision& _collision);

	void OnTriggerEnter(const Collision& _collision);
	void OnTriggerStay(const Collision& _collision);
	void OnTriggerExit(const Collision& _collision);


	unsigned int GetID() const { return m_ID; }
	COLLIDER_TYPE GetColliderType() const { return m_type; }

	// ���� �浹���� �浹ü ���� ��ȯ
	int GetCurrentCollison() { return m_currentCollision; }

	/// �浹�����Լ� 
	virtual bool Collides(Vector2 _position) = 0;
	virtual bool Collides(CircleCollider* _circle) = 0;
	virtual bool Collides(BoxCollider* _box) = 0;

	bool Collides(Collider* _collider);

	/// Broadphase ����

	virtual Vector2 GetMinPoint()const = 0;
	virtual Vector2 GetMaxPoint()const = 0;

	Node* GetNode(){ return m_node;}
	void SetNode(Node* _node)
	{ m_node = _node; }

	void SetTrigger(bool _isTrigger) { m_isTrigger = _isTrigger; }
	bool IsTrigger() const{ return m_isTrigger; }
private:
	// �浹ü�� ���̵�� ������ ���� ������.
	const unsigned int m_ID;
	int m_currentCollision; // ���� �浹���� �浹ü ���� 

	COLLIDER_TYPE m_type;
	// ObjectType ��ŭ �ڽŰ� �����ϴ� ��尡 �����Ƿ�
	// AABBTree�� �ش��ϴ� ����� �����͸� type���� ������.
	Node* m_node;

	// ������ ȿ���� ���� �ʴ� Ʈ���� ����
	bool m_isTrigger; 
};

/// �ݶ��̴� �浹���� ������ Key���� �����
union ColliderKey
{
	ColliderKey(Collider* _c1, Collider* _c2) :Key(0)
	{
		ColliderID1 = FMath::Min(_c1->GetID(), _c2->GetID());
		ColliderID2 = FMath::Max(_c1->GetID(), _c2->GetID());
	}

	struct
	{
		unsigned int ColliderID1;
		unsigned int ColliderID2;
	};

	unsigned long long Key;
};

/// ColliderKey�� �ʿ��� ����ϴ� ���ľ˰���
inline bool operator <(const ColliderKey& c1, const ColliderKey& c2)
{
	if (c1.Key < c2.Key)
		return true;

	return false;
}