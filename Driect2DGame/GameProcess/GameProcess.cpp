
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

	// 매니저 메모리 공간 할당
	m_timeManager = new TimeManager();
	m_inputManager = new InputManager();
	m_collisionManager = new CollisionManager();
	m_sceneManager = new SceneManager();
	m_pathManager = new PathManager();
	m_UIManager = new UIManager();

	// 매니저 초기화
	m_pathManager->Initalize();
	m_timeManager->Initalize();
	m_inputManager->Initalize(m_hWnd);
	m_sceneManager->Initalize(m_inputManager,m_collisionManager);
	m_collisionManager->Initalize(m_inputManager, m_sceneManager);
	m_UIManager->Initalize(m_sceneManager);

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
	constexpr float fixedDeltaTime = 0.02f; // 50프레임 주기
	m_elapsedTime += deltaTime;

	while (m_elapsedTime >= fixedDeltaTime)
	{
		m_elapsedTime -= fixedDeltaTime;
		m_sceneManager->FixedUpdate(fixedDeltaTime);
		//  ======== 충돌처리 ============
		m_collisionManager->Update();
	}

	// ========== 게임오브젝트 업데이트 ==============
	m_sceneManager->Update(deltaTime);
	m_sceneManager->LateUpdate(deltaTime);
	
	// ============= UI 이벤트 ====================== 
	m_UIManager->Update();
	
	// ================= 랜더링 ===================
	// 랜더링은 BegineRender와 EndRender 사이에 해야한다.
	m_d2DRenderer->BeginRender();

	m_sceneManager->Render(m_d2DRenderer);
	m_timeManager->DebugRender(m_d2DRenderer);

	m_d2DRenderer->EndRender();
	// =============== 이벤트 처리 =================

}

void GameProcess::Finalize()
{
	m_sceneManager->Finalize();
	m_collisionManager->Finalize();
	m_inputManager->Finalize();
	m_timeManager->Finalize();
	m_UIManager->Finalize();

	// 메모리 해제
	delete m_sceneManager;
	delete m_collisionManager;
	delete m_timeManager;
	delete m_inputManager;
	delete m_UIManager;
}
