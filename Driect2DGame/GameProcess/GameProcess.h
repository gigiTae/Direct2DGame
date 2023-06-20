#pragma once


class D2DRenderer;
class InputManager;
class TimeManager;
class CollisionManager;
class SceneManager;

/// <summary>
///  게임진행을 담당하는 클래스이다
/// 
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

private:
	float m_elapsedTime;
	// 메인 윈도우 핸들 
	HWND m_hWnd; 
	// 랜더러
	D2DRenderer* m_d2DRenderer;

	// 매니져 
	SceneManager* m_sceneManager;
	InputManager* m_inputManager;
	TimeManager* m_timeManager;
	CollisionManager* m_collisionManager;

};

