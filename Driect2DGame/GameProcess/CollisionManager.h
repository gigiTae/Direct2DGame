#pragma once

// ���漱��
class Collider;
class BoxCollider;
class CircleCollider;
class InputManager;
class SceneManager;
class GameObject;
class AABBTree;

// �浹���� 
struct Collision
{
	GameObject* otherObject;
	Collider* otherCollider;
	COLLIDER_TYPE type;
};

union CollisionID
{
	struct 
	{
		unsigned int leftID;
		unsigned int rightID;
	};
	unsigned long long ID;
};

struct ColliderKey
{
	ColliderKey(Collider* _c1, Collider* _c2)
	{
		if (_c1 < _c2)
		{
			collider1 = _c1, collider2 = _c2;
		}
		else
		{
			collider1 = _c2, collider2 = _c1;
		}
	}

	Collider* collider1;
	Collider* collider2;
};

// ���������Ӱ� �̹��������� �浹������ ������ �ִ´� 
struct CollisionInfomation
{
	bool prevCollision;
	bool currentCollision;
};

/// <summary>
///  �浹�� �����ϴ� �Ŵ����̴�.
/// �߰�������δ� �پ��� collider�� �����ϰ� 
/// �׿� �°� �Ŵ����� collider�� ������ ���� 
/// �浹������ �����ϰ� �������ش�.
/// </summary>
class CollisionManager
{
public:
	// ColliderID�� �߱��ϴ� �Լ�
	static unsigned int GetColliderID() { static unsigned int ID = 0; return ID++; }  

public:
	CollisionManager();
	~CollisionManager();

	void Initalize(InputManager* _inputManager, SceneManager* _sceneManager);
	void Update();
	void Finalize();

public:

	// ������Ʈ Ÿ�԰� Ÿ�԰��� �浹������ �Ѵ�.
	void CheckCollisionObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right) const;
	void AddColider(Collider* _collider) const;

private:

	// �� ������Ʈ�� �浹�ϴ� Ÿ������ ��ȯ�ϴ� �Լ�
	bool IsCollisionType(OBJECT_TYPE _left, OBJECT_TYPE _right);

	
private:
	InputManager* m_inputManager;
	SceneManager* m_sceneManager;

	// Boradphase �˰��� 
	AABBTree* m_aabbTree; 
	// ���� ������ �浹�������� ����
	map<ColliderKey, CollisionInfomation> m_collisionInfo;

	// ������Ʈ Ÿ�Ժ��� �浹�� �Ǵ� const �Ŵ������� ���������ϰ� mutable�� ����
	mutable int m_collisionCheck[static_cast<int>(OBJECT_TYPE::END)];
};

inline bool operator <(const ColliderKey& c1, const ColliderKey& c2)
{
	if (c1.collider1 < c2.collider1)
		return true;

	if (c1.collider1 == c2.collider1 && c1.collider2 < c2.collider2)
		return true;

	return false;
}