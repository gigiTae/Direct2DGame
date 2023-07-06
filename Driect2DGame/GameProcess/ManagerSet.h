#pragma once

// 전방선언
class D2DRenderer;
class InputManager;
class TimeManager;
class CollisionManager;
class SceneManager;
class PathManager;
class UIManager;


/// <summary>
/// 게임프로세의 매니저들을 포인터로 
/// 가지고 있는 클래스이다 
/// 반환은 항상 const로 하기때문에 
/// const 함수가 아닌 매니져함수는 접근이 불가능하게 설계
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

	/// const로 반환해서 const 함수들만 접근이 가능하다.
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

