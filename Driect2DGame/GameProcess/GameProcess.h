#pragma once


class D2DRenderer;
class InputManager;
class TimeManager;
class CollisionManager;
class SceneManager;
class PathManager;
class UIManager;

/// <summary>
///  ���������� ����ϴ� Ŭ�����̴�
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

	bool IsGameRunning() { return m_gameRunnig; }
	void EndGame() { m_gameRunnig = false; }
private:
	/// ���� ���� ���μ����� �����Ǵ�
	bool m_gameRunnig;

	float m_elapsedTime;

	// ���� ������ �ڵ� 
	HWND m_hWnd; 
	// ������
	D2DRenderer* m_d2DRenderer;

	// �Ŵ��� 
	SceneManager* m_sceneManager;
	InputManager* m_inputManager;
	TimeManager* m_timeManager;
	CollisionManager* m_collisionManager;
	PathManager* m_pathManager;
	UIManager* m_UIManager;
};

