#pragma once

// 전방선언
class D2DRenderer;
class InputManager;
class TimeManager;
class CollisionManager;
class SceneManager;
class PathManager;
class CameraManager;
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
	ManagerSet() = default;
	~ManagerSet();

	void Initalize(PathManager* _pathManager,
		InputManager* _inputManager,
		TimeManager* _timeManager,
		SceneManager* _sceneManager,
		UIManager* _UIManager,
		CollisionManager* _collisionManager,
		CameraManager* _cameraManager);

	const PathManager* GetPathManager()const { return m_pathManager; }
	const InputManager* GetInputManager()const { return m_inputManager; }
	const TimeManager* GetTimeManager()const {return m_timeManager;}
	const SceneManager* GetSceneManager()const { return m_sceneManager; }
	const UIManager* GetUIManager()const { return m_UIManager; }
	const CollisionManager* GetCollisionManager()const { return m_collisionManager; }
	const CameraManager* GetCameraManager()const { return m_cameraManager; }

private:
	CameraManager* m_cameraManager;
	PathManager* m_pathManager;
	InputManager* m_inputManager;
	TimeManager* m_timeManager;
	SceneManager* m_sceneManager;
	UIManager* m_UIManager;
	CollisionManager* m_collisionManager;
};
