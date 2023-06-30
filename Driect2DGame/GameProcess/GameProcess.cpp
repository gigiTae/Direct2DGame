
#include "GameProcessPCH.h"
#include "GameProcess.h"
#include "TimeManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "PathManager.h"

GameProcess::GameProcess()
	:m_collisionManager(nullptr)
	, m_sceneManager(nullptr)
	, m_inputManager(nullptr)
	, m_timeManager(nullptr)
	,m_pathManager(nullptr)
	, m_d2DRenderer(nullptr)
	, m_hWnd(nullptr)
	,m_UIManager(nullptr)
	,m_elapsedTime(0.f)
	,m_gameRunnig(false)
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
	m_pathManager = new PathManager();
	m_UIManager = new UIManager();

	// �Ŵ��� �ʱ�ȭ
	m_pathManager->Initalize();
	m_timeManager->Initalize();
	m_inputManager->Initalize(m_hWnd);
	m_sceneManager->Initalize(m_inputManager,m_collisionManager);
	m_collisionManager->Initalize(m_inputManager, m_sceneManager);
	m_UIManager->Initalize(m_sceneManager);

	// ���� ���� Ȱ��ȭ
	m_gameRunnig = true;
}

void GameProcess::Process()
{
	/// ���ӿ��� ���� �ٽ����� �κ����� 
	/// ��� ������Ʈ�� �Լ� ȣ�� ������ ��Ÿ���� �����̴�.

	float deltaTime = static_cast<float>(m_timeManager->Update());
	m_inputManager->Update();

	// ==================���� ó��===================
	constexpr float fixedDeltaTime = 0.02f; // 50������ �ֱ�
	m_elapsedTime += deltaTime;

	while (m_elapsedTime >= fixedDeltaTime)
	{
		m_elapsedTime -= fixedDeltaTime;
		m_sceneManager->FixedUpdate(fixedDeltaTime);
		//  ======== �浹ó�� ============
		m_collisionManager->Update();
	}

	// ========== ���ӿ�����Ʈ ������Ʈ ==============
	m_sceneManager->Update(deltaTime);
	m_sceneManager->LateUpdate(deltaTime);
	
	// ============= UI �̺�Ʈ ====================== 
	m_UIManager->Update();
	
	// ================= ������ ===================
	// �������� BegineRender�� EndRender ���̿� �ؾ��Ѵ�.
	m_d2DRenderer->BeginRender();

	m_sceneManager->Render(m_d2DRenderer);
	m_timeManager->DebugRender(m_d2DRenderer);

	m_d2DRenderer->EndRender();
	// =============== �̺�Ʈ ó�� =================

}

void GameProcess::Finalize()
{
	m_sceneManager->Finalize();
	m_collisionManager->Finalize();
	m_inputManager->Finalize();
	m_timeManager->Finalize();
	m_UIManager->Finalize();

	// �޸� ����
	delete m_sceneManager;
	delete m_collisionManager;
	delete m_timeManager;
	delete m_inputManager;
	delete m_UIManager;
}
