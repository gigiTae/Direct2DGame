#pragma once

// ���漱��
class D2DRenderer;
class InputManager;
class TimeManager;
class CollisionManager;
class SceneManager;
class PathManager;
class UIManager;


/// <summary>
/// �������μ��� �Ŵ������� �����ͷ� 
/// ������ �ִ� Ŭ�����̴� 
/// ��ȯ�� �׻� const�� �ϱ⶧���� 
/// const �Լ��� �ƴ� �Ŵ����Լ��� ������ �Ұ����ϰ� ����
/// </summary>
class ManagerSet
{
public:
	ManagerSet() = default;
	~ManagerSet();

	void Initalize(PathManager* _pathManager,
		InputManager* _inputManager,
		TimeManager* _timeManager,
		SceneManager* _sceneManager,
		UIManager* _UIManager,
		CollisionManager* _collisionManager);

	const PathManager* GetPathManager()const { return m_pathManager; }
	const InputManager* GetInputManager()const { return m_inputManager; }
	const TimeManager* GetTimeManager()const {return m_timeManager;}
	const SceneManager* GetSceneManager()const { return m_sceneManager; }
	const UIManager* GetUIManager()const { return m_UIManager; }
	const CollisionManager* GetCollisionManager()const { return m_collisionManager; }

private:
	PathManager* m_pathManager;
	InputManager* m_inputManager;
	TimeManager* m_timeManager;
	SceneManager* m_sceneManager;
	UIManager* m_UIManager;
	CollisionManager* m_collisionManager;
};
