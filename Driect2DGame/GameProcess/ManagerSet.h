#pragma once

#include "Manager.h"

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
	string name = typeid(T).name();

	if (name == "class InputManager")
	{
		return  reinterpret_cast<T*>(m_inputManager);
	}
	else if (name == "class TimeManager")
	{
		return reinterpret_cast<T*>(m_timeManager);
	}
	else if (name == "class SceneManager")
	{
		return reinterpret_cast<T*>(m_sceneManager);
	}
	else if (name == "class UIManager")
	{
		return  reinterpret_cast<T*>(m_UIManager);
	} 
	else if (name == "class CollisionManager")
	{
		return reinterpret_cast<T*>(m_collisionManager);
	}
	else if (name == "class PathManager")
	{
		return  reinterpret_cast<T*>(m_pathManager);
	}
	return nullptr;
}

