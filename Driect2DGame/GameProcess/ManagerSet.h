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
	ManagerSet() =default;
	~ManagerSet();

	void Initalize(PathManager* _pathManager,
		InputManager* _inputManager,
		TimeManager* _timeManager,
		SceneManager* _sceneManager,
		UIManager* _UIManager,
		CollisionManager* _collisionManager);

	/// const�� ��ȯ�ؼ� const �Լ��鸸 ������ �����ϴ�.
	template <typename T> 
	const T* GetManager() const;

private:
	PathManager* m_pathManager;
	InputManager* m_inputManager;
	TimeManager* m_timeManager;
	SceneManager* m_sceneManager;
	UIManager* m_UIManager;
	CollisionManager* m_collisionManager;
};

template <typename T>
const T* ManagerSet::GetManager() const
{
	const char* name = typeid(T).name();

	switch (name)
	{
	case "class TimeManager":
		return m_timeManager;
	
	case "class SceneManager":
		return m_sceneManager;

	case "class UIManager":
		return m_UIManager;
		
	case "class InputManager":
		return m_inputManager;

	case "class CollisionManager":
		return m_collisionManager;
	default:
		break;
	}

	return nullptr;
}

