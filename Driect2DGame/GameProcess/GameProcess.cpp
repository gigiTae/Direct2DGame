
#include "GameProcessPCH.h"
#include "GameProcess.h"
#include "TimeManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "SceneManager.h"

GameProcess::GameProcess()
	:m_collisionManager(nullptr)
	, m_sceneManager(nullptr)
	, m_inputManager(nullptr)
	, m_timeManager(nullptr)
	, m_d2DRenderer(nullptr)
	, m_hWnd(nullptr)

{
}

GameProcess::~GameProcess()
{
}


void GameProcess::Initalize(D2DRenderer* _d2DRenderer, HWND _main)
{
	m_d2DRenderer = _d2DRenderer;
	m_hWnd = _main;

	// �Ŵ��� �޸� ���� �Ҵ�
	m_timeManager = new TimeManager();
	m_inputManager = new InputManager();
	m_collisionManager = new CollisionManager();
	m_sceneManager = new SceneManager();

	// �Ŵ��� �ʱ�ȭ
	m_timeManager->Initalize();
	m_inputManager->Initalize(m_hWnd);
	m_sceneManager->Initalize(m_inputManager);
	m_collisionManager->Initalize(m_inputManager, m_sceneManager);
}

void GameProcess::Roop()
{
	double deltaTime = m_timeManager->Update();
	m_inputManager->Update();


	// ���ӿ�����Ʈ ������Ʈ



	// �浹ó��
	m_collisionManager->Update();

	// ������ 
	m_d2DRenderer->BeginRender();


	m_d2DRenderer->EndRender();


}

void GameProcess::Finalize()
{



}
