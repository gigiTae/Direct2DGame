#pragma once


/// 전방선언

class D2DRenderer;
class InputManager;
class TimeManager;
class CollisionManager;
class SceneManager;
class PathManager;
class ResourceManager;
class UIManager;

/// <summary>
///  게임진행을 담당하는 클래스이다
///  모든 매니져들을 관리한다.
/// 
/// </summary>
class GameProcess
{
public:
	GameProcess();
	~GameProcess();

	void Initalize(D2DRenderer* _d2DRenderer, HWND _main);
	void Process();
	void Finalize();

	bool IsGameRunning() { return m_gameRunnig; }
	void EndGame() { m_gameRunnig = false; }
private:
	bool ShowDubg();

private:
	/// 현재 게임 프로세스가 진행판단
	bool m_gameRunnig;

	/// 이번 프레임에 디버그 정보를 표시하는지
	bool m_showDebug;

 	float m_elapsedTime;

	// 메인 윈도우 핸들 
	HWND m_hWnd; 
	// 랜더러
	D2DRenderer* m_d2DRenderer;

	Vector2 m_screenSize; 

	// 매니져 
	SceneManager* m_sceneManager;
	InputManager* m_inputManager;
	TimeManager* m_timeManager;
	CollisionManager* m_collisionManager;
	PathManager* m_pathManager;
	ResourceManager* m_resourceManager;
	UIManager* m_UIManager;
};

