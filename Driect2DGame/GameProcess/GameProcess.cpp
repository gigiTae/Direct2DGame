
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

	// 매니저 메모리 공간 할당
	m_timeManager = new TimeManager();
	m_inputManager = new InputManager();
	m_collisionManager = new CollisionManager();
	m_sceneManager = new SceneManager();

	// 매니저 초기화
	m_timeManager->Initalize();
	m_inputManager->Initalize(m_hWnd);
	m_sceneManager->Initalize(m_inputManager);
	m_collisionManager->Initalize(m_inputManager, m_sceneManager);
}

void GameProcess::Roop()
{
	float deltaTime = m_timeManager->Update();
	m_inputManager->Update();


	// 게임오브젝트 업데이트
	m_sceneManager->Update(deltaTime);
	m_sceneManager->FinalUpdate(deltaTime);
	
	// 충돌처리
	m_collisionManager->Update();



	// 랜더링은 BegineRender와 EndRender 사이에 해야한다.
	m_d2DRenderer->BeginRender();
	
	m_sceneManager->Render(m_d2DRenderer);

	m_d2DRenderer->EndRender();


}

void GameProcess::Finalize()
{



}
