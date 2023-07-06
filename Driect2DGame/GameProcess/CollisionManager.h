#pragma once

#include "Manager.h"

// ���漱��
class Collider;
class BoxCollider;
class CircleCollider;
class InputManager;
class SceneManager;
class GameObject;


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

/// <summary>
///  �浿�� �����ϴ� �Ŵ����̴�.
/// �߰�������δ� �پ��� collider�� �����ϰ� 
/// �׿� �°� �Ŵ����� collider�� ������ ���� 
/// �浹������ �����ϰ� �������ش�.
/// </summary>
class CollisionManager : public Manager
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
	void CheckCollisionObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right);
	
private:

	// �浹ü���� ID�� �����ؼ� ID�� �ش��ϴ� ���ͷ����͸� ��ȯ
	void CheckID(const Collider* _left, const Collider* _right, map<unsigned long long, bool>::iterator& iter);

	// �� �浹ü�� �浹���� �Ǵ��ϴ� �Լ� 
    bool IsCollision(BoxCollider* _leftBox, BoxCollider* _rightBox) const ;
	bool IsCollision(BoxCollider* _leftBox, CircleCollider* _rightCircle) const;
	bool IsCollision(CircleCollider* _leftCircle, CircleCollider* _rightCircle) const ;

	// �浹�� �Ǵ����Ŀ� ������ �ݶ��̴��鿡�� �浹ó���� �������� ����
	void OnCollisionProcess(bool _istCollision, map<unsigned long long, bool>::iterator& iter, Collider* _left, Collider* _right);

	// �浹ü���� ID�� �����ϴ� �Լ�
	const CollisionID CombineID(unsigned int _left, unsigned int _right);
	void CollisionGroupUpdate(OBJECT_TYPE _left, OBJECT_TYPE _right);

private:
	InputManager* m_inputManager;
	SceneManager* m_sceneManager;

	// ���� ������ �浹�������� ����
	map<unsigned long long, bool> m_prevCollisionInfo;
	// ������Ʈ Ÿ�Ժ��� �浹�� �Ǵ�
	int m_collisionCheck[static_cast<int>(OBJECT_TYPE::END)];
};

