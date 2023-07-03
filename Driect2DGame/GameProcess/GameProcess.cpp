
#include "GameProcessPCH.h"
#include "GameProcess.h"
#include "TimeManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "PathManager.h"
#include "ResourceManager.h"

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
	,m_showDebug(false)
	,m_screenSize{}
{
}

GameProcess::~GameProcess()
{
}


void GameProcess::Initalize(D2DRenderer* _d2DRenderer, HWND _main)
{
	m_d2DRenderer = _d2DRenderer;
	m_hWnd = _main;

	RECT rc{};
	// â Ŭ���̾�Ʈ ���� ��ǥ
	GetClientRect(m_hWnd, &rc);

	m_screenSize = Vector2(static_cast<float>(rc.right - rc.left), static_cast<float>(rc.bottom - rc.top));

	// �Ŵ��� �޸� ���� �Ҵ�
	m_timeManager = new TimeManager();
	m_inputManager = new InputManager();
	m_collisionManager = new CollisionManager();
	m_sceneManager = new SceneManager();
	m_pathManager = new PathManager();
	m_UIManager = new UIManager();
	m_resourceManager = new ResourceManager();

	// �Ŵ��� �ʱ�ȭ
	m_pathManager->Initalize();
	m_timeManager->Initalize(m_screenSize);
	m_inputManager->Initalize(m_hWnd);
	m_resourceManager->Initalize(_d2DRenderer);
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
	constexpr float FIXED_DELTA_TIME = 0.02f; // 50������ �ֱ�
	m_elapsedTime += deltaTime;

	while (m_elapsedTime >= FIXED_DELTA_TIME)
	{
		m_elapsedTime -= FIXED_DELTA_TIME;
		m_sceneManager->FixedUpdate(FIXED_DELTA_TIME);
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

	// ��������� ������
	if (ShowDubg())
	{
		m_sceneManager->DebugRender(m_d2DRenderer);
		m_timeManager->DebugRender(m_d2DRenderer);
	}

	m_d2DRenderer->EndRender();

	// =============== �ļ�ó�� =================
	// ex) ������Ʈ ����, �߰�, �� ����
	m_sceneManager->ProcessEvent();
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
	delete m_pathManager;
	delete m_collisionManager;
	delete m_timeManager;
	delete m_inputManager;
	delete m_UIManager;
}

bool GameProcess::ShowDubg()
{
	if (m_inputManager->IsKeyState(KEY::F5, KEY_STATE::TAP))
	{
		m_showDebug = !m_showDebug;
	}
	return m_showDebug;
}
