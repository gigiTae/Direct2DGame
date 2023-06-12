#pragma once


// ���漱��
class Collider;
class BoxCollider;
class CircleCollier;
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

/// <summary>
///  �浿�� �����ϴ� �Ŵ����̴�.
/// �߰�������δ� �پ��� collider�� �����ϰ� 
/// �׿� �°� �Ŵ����� collider�� ������ ���� 
/// �浹������ �����ϰ� �������ش�.
/// </summary>
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Initalize(InputManager* _inputManager, SceneManager* _sceneManager);
	void Update();
	void Finalize();

private:
	InputManager* m_inputManager;
	SceneManager* m_sceneManager;

};

