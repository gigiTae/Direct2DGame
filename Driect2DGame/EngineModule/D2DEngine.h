#pragma once


// ���漱���� ���ؼ� �̳��� �ִ�!
class GameProcess;
class D2DRenderer;

class GameProcess;

/// <summary>
/// ���ӿ� �ʿ��� ������ ��������~! 
/// 1.���� ������ �׷��� ����� ����� ����
/// 2.������ ���� ���μ����� ������ ����� �´°ɱ�?
/// 3.D2D ��������� �߻���غ���
/// 
/// 
/// 2023.06.10 �̱���
/// </summary>
class D2DEngine
{
public:
	D2DEngine();
	~D2DEngine();
	
	// ���� ����� �ʱ�ȭ �Լ� 
	void Initalize(HINSTANCE _hInstance, int _nCmdShow);

	void Process();

	// ���� ����� ���� �Լ�
	void Finalize();
private:
	void WindowInitalize(HINSTANCE _hInstance, int _nCmdShow);

private:
	HINSTANCE m_hInstance;
	// ���� ������ �ڵ�
	HWND m_hWnd;
	// �������� ���
	D2DRenderer* m_d2DRenderer;
	// ���� ������ ���
	GameProcess* m_gameProcess;
};

