#pragma once


// ���漱��
class BoxCollider;
class CircleCollier;
class InputManager;
class SceneManager;

// �浹�� �߻��ϸ� �浹������ �Ѱ��ش�. 
struct CollisionInfo
{

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

