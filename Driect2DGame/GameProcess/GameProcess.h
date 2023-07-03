#pragma once


/// ���漱��

class D2DRenderer;
class InputManager;
class TimeManager;
class CollisionManager;
class SceneManager;
class PathManager;
class ResourceManager;
class UIManager;

/// <summary>
///  ���������� ����ϴ� Ŭ�����̴�
///  ��� �Ŵ������� �����Ѵ�.
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
	/// ���� ���� ���μ����� �����Ǵ�
	bool m_gameRunnig;

	/// �̹� �����ӿ� ����� ������ ǥ���ϴ���
	bool m_showDebug;

 	float m_elapsedTime;

	// ���� ������ �ڵ� 
	HWND m_hWnd; 
	// ������
	D2DRenderer* m_d2DRenderer;

	Vector2 m_screenSize; 

	// �Ŵ��� 
	SceneManager* m_sceneManager;
	InputManager* m_inputManager;
	TimeManager* m_timeManager;
	CollisionManager* m_collisionManager;
	PathManager* m_pathManager;
	ResourceManager* m_resourceManager;
	UIManager* m_UIManager;
};

