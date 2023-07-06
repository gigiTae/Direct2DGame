#pragma once

#include "Manager.h"

// 전방선언
class Collider;
class BoxCollider;
class CircleCollider;
class InputManager;
class SceneManager;
class GameObject;


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

/// <summary>
///  충동을 관리하는 매니져이다.
/// 추가기능으로는 다양한 collider를 구현하고 
/// 그에 맞게 매니져는 collider의 종류에 따라서 
/// 충돌정보를 생성하고 전달해준다.
/// </summary>
class CollisionManager : public Manager
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
	void CheckCollisionObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right);
	
private:

	// 충돌체간의 ID를 조합해서 ID에 해당하는 이터레이터를 반환
	void CheckID(const Collider* _left, const Collider* _right, map<unsigned long long, bool>::iterator& iter);

	// 두 충돌체가 충돌한지 판단하는 함수 
    bool IsCollision(BoxCollider* _leftBox, BoxCollider* _rightBox) const ;
	bool IsCollision(BoxCollider* _leftBox, CircleCollider* _rightCircle) const;
	bool IsCollision(CircleCollider* _leftCircle, CircleCollider* _rightCircle) const ;

	// 충돌을 판단한후에 각각의 콜라이더들에게 충돌처리후 정보들을 전달
	void OnCollisionProcess(bool _istCollision, map<unsigned long long, bool>::iterator& iter, Collider* _left, Collider* _right);

	// 충돌체간의 ID를 조합하는 함수
	const CollisionID CombineID(unsigned int _left, unsigned int _right);
	void CollisionGroupUpdate(OBJECT_TYPE _left, OBJECT_TYPE _right);

private:
	InputManager* m_inputManager;
	SceneManager* m_sceneManager;

	// 이전 프레임 충돌정보들을 저장
	map<unsigned long long, bool> m_prevCollisionInfo;
	// 오브젝트 타입별로 충돌을 판단
	int m_collisionCheck[static_cast<int>(OBJECT_TYPE::END)];
};

