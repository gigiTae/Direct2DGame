
#include "GameProcessPCH.h"
#include "GameProcess.h"
#include "TimeManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "PathManager.h"
#include "NamingManager.h"
#include "ManagerSet.h"

GameProcess::GameProcess()
	:m_collisionManager(nullptr)
	, m_sceneManager(nullptr)
	, m_inputManager(nullptr)
	, m_timeManager(nullptr)
	, m_pathManager(nullptr)
	, m_d2DRenderer(nullptr)
	, m_hWnd(nullptr)
	, m_UIManager(nullptr)
	, m_elapsedTime(0.f)
	, m_gameRunnig(false)
	, m_showDebug(false)
	, m_screenSize{}
	, m_managerSet(nullptr)
{}

GameProcess::~GameProcess()
{
}


void GameProcess::Initalize(D2DRenderer* _d2DRenderer, HWND _main)
{
	m_d2DRenderer = _d2DRenderer;
	m_hWnd = _main;

	RECT rc{};
	// 창 클라이언트 영역 좌표
	GetClientRect(m_hWnd, &rc);

	m_screenSize = Vector2(static_cast<float>(rc.right - rc.left), static_cast<float>(rc.bottom - rc.top));

	// 매니저 메모리 공간 할당
	m_timeManager = new TimeManager();
	m_inputManager = new InputManager();
	m_collisionManager = new CollisionManager();
	m_sceneManager = new SceneManager();
	m_pathManager = new PathManager();
	m_UIManager = new UIManager();

	// 매니저 초기화
	m_pathManager->Initalize();
	m_timeManager->Initalize(m_screenSize);
	m_inputManager->Initalize(m_hWnd);
	m_collisionManager->Initalize(m_inputManager, m_sceneManager);
	m_UIManager->Initalize(m_sceneManager);
	m_sceneManager->Initalize(_d2DRenderer,m_inputManager, m_collisionManager);

	// 매니져 셋 초기화
	m_managerSet = new ManagerSet();
	m_managerSet->Initalize(m_pathManager, m_inputManager
		, m_timeManager, m_sceneManager, m_UIManager, m_collisionManager);

	// 게임 루프 활성화
	m_gameRunnig = true;
}

void GameProcess::Process()
{
	/// 게임에서 가장 핵심적인 부분으로 
	/// 모든 오브젝트의 함수 호출 순서를 나타내는 지점이다.

	float deltaTime = static_cast<float>(m_timeManager->Update());
	m_inputManager->Update();

	// ==================물리 처리===================
	constexpr float FIXED_DELTA_TIME = 0.02f; // 50프레임 주기
	m_elapsedTime += deltaTime;

	while (m_elapsedTime >= FIXED_DELTA_TIME)
	{
		m_elapsedTime -= FIXED_DELTA_TIME;
		m_sceneManager->FixedUpdate(FIXED_DELTA_TIME);
	}

	// ========== 게임오브젝트 업데이트 ==============
	m_sceneManager->Update(deltaTime);
	m_sceneManager->LateUpdate(deltaTime);
	
	//  ======== 충돌처리 ============================
	m_collisionManager->Update();
	
	// ============= UI 이벤트 ====================== 
	m_UIManager->Update();
	
	// ================= 랜더링 ===================
	// 랜더링은 BegineRender와 EndRender 사이에 해야한다.
	m_d2DRenderer->BeginRender();

	m_sceneManager->Render(m_d2DRenderer);

	// 디버그정보 랜더링
	if (ShowDubg())
	{
		m_sceneManager->DebugRender(m_d2DRenderer);
		m_timeManager->DebugRender(m_d2DRenderer);
	}

	m_d2DRenderer->EndRender();

	// =============== 후속처리 =================
	// ex) 오브젝트 삭제, 추가, 씬 변경
	m_sceneManager->ProcessEvent();
	
	/// 게임을 종료
	m_gameRunnig = m_sceneManager->IsGameRun();
}

void GameProcess::Finalize()
{
	m_sceneManager->Finalize();
	m_collisionManager->Finalize();
	m_inputManager->Finalize();
	m_timeManager->Finalize();
	m_UIManager->Finalize();
	
	NamingManager::Finalize();

	// 메모리 해제
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
