
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
	,m_elapsedTime(0.f)
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
	m_sceneManager->Initalize(m_inputManager,m_collisionManager);
	m_collisionManager->Initalize(m_inputManager, m_sceneManager);
}

void GameProcess::Process()
{
	float deltaTime = static_cast<float>(m_timeManager->Update());
	m_inputManager->Update();

	// ==================���� ó��===================
	static constexpr float fixedDeltaTime = 0.2f; // 50������ �ֱ�
	m_elapsedTime += deltaTime;

	while (m_elapsedTime >= fixedDeltaTime)
	{
		m_elapsedTime -= fixedDeltaTime;
		m_sceneManager->FixedUpdate(fixedDeltaTime);
		// �浹ó��
		m_collisionManager->Update();
	}
	// =============================================

	// ���ӿ�����Ʈ ������Ʈ
	m_sceneManager->Update(deltaTime);
	m_sceneManager->FinalUpdate(deltaTime);  
	
	// �������� BegineRender�� EndRender ���̿� �ؾ��Ѵ�.
	m_d2DRenderer->BeginRender();
	
	m_sceneManager->Render(m_d2DRenderer);

	m_d2DRenderer->EndRender();


}

void GameProcess::Finalize()
{
	m_sceneManager->Finalize();
	m_collisionManager->Finalize();
	m_inputManager->Finalize();
	m_timeManager->Finalize();

	// �޸� ����
	delete m_sceneManager;
	delete m_collisionManager;
	delete m_timeManager;
	delete m_inputManager;

}
