#pragma once


class D2DRenderer;
class InputManager;
class TimeManager;
class CollisionManager;
class SceneManager;

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

private:
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

};

