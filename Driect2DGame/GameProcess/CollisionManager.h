#pragma once

// 전방선언
class Collider;
class BoxCollider;
class CircleCollider;
class InputManager;
class SceneManager;
class GameObject;
class AABBTree;

// 충돌정보 
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

// 이전프레임과 이번프레임의 충돌정보를 가지고 있는다 
struct CollisionInfomation
{
	bool prevCollision;
	bool currentCollision;
};

/// <summary>
///  충돌을 관리하는 매니져이다.
/// 추가기능으로는 다양한 collider를 구현하고 
/// 그에 맞게 매니져는 collider의 종류에 따라서 
/// 충돌정보를 생성하고 전달해준다.
/// </summary>
class CollisionManager
{
public:
	// ColliderID를 발급하는 함수
	static unsigned int GetColliderID() { static unsigned int ID = 0; return ID++; }  

public:
	CollisionManager();
	~CollisionManager();

	void Initalize(InputManager* _inputManager, SceneManager* _sceneManager);
	void Update();
	void Finalize();

public:

	// 오브젝트 타입과 타입간의 충돌설정을 한다.
	void CheckCollisionObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right) const;
	void AddColider(Collider* _collider) const;

private:

	// 두 오브젝트가 충돌하는 타입인지 반환하는 함수
	bool IsCollisionType(OBJECT_TYPE _left, OBJECT_TYPE _right);

	
private:
	InputManager* m_inputManager;
	SceneManager* m_sceneManager;

	// Boradphase 알고리즘 
	AABBTree* m_aabbTree; 
	// 이전 프레임 충돌정보들을 저장
	map<ColliderKey, CollisionInfomation> m_collisionInfo;

	// 오브젝트 타입별로 충돌을 판단 const 매니져에서 수정가능하게 mutable로 오픈
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