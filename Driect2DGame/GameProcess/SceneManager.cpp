#include "GameProcessPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "MainScene.h"
#include "InputManager.h"
#include "ManagerSet.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "UIManager.h"

SceneManager::SceneManager()
	:m_currentScene(nullptr)
	,m_d2DRenderer(nullptr)
	,m_sceneList{}
	,m_gameRun(false)
	,m_managerSet(nullptr)
	,m_collisionManager(nullptr)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initalize(D2DRenderer* _d2DRenderer, ManagerSet* _managerSet, CollisionManager* _collisionManager)
{
	m_gameRun = true;
	m_d2DRenderer = _d2DRenderer;
	m_managerSet = _managerSet;
	m_collisionManager = _collisionManager;

	// 씬 메모리 공간할당
	m_sceneList[static_cast<int>(SCENE_TYPE::MAIN)] = new MainScene();

	// 씬 명시적 초기화
	m_sceneList[static_cast<int>(SCENE_TYPE::MAIN)]->Initalize(_d2DRenderer, m_managerSet, this);

	// 현재씬을 지정한다
	m_currentScene = m_sceneList[static_cast<int>(SCENE_TYPE::MAIN)];

	m_currentScene->Enter();
}

void SceneManager::ChangeScene(SCENE_TYPE _nextScene)
{
	m_currentScene->Exit();
	m_collisionManager->Clear();
	m_managerSet->GetUIManager()->SetFocusedUI(nullptr);
	m_managerSet->GetCameraManager()->ResetCamera();

	if (_nextScene == SCENE_TYPE::END)
	{
		m_gameRun = false;
		return;
	}

	m_currentScene = m_sceneList[static_cast<int>(_nextScene)];
	m_currentScene->Enter();
}

void SceneManager::Finalize()
{
	for (int i = 0; i < static_cast<int>(SCENE_TYPE::END); ++i)
	{
		if (nullptr != m_sceneList[i])
		{
			m_sceneList[i]->Finalize();
			delete m_sceneList[i];
		}
	}
}

void SceneManager::RegisterNextScene(SCENE_TYPE _nextScene) const
{
	m_currentScene->RegisterNextScene(_nextScene);
}
 
void SceneManager::RegisterObject(GameObject* _object, float _delayTime /*=0.f*/) const
{
	m_currentScene->RegisterObject(_object, _delayTime);
}


void SceneManager::Update(float _deltaTime)
{
	m_currentScene->Update(_deltaTime);
}

void SceneManager::FixedUpdate(float _fiexedDeltaTime)
{
	m_currentScene->FixedUpdate(_fiexedDeltaTime);
}

void SceneManager::LateUpdate(float _deltaTime)
{
	m_currentScene->LateUpdate(_deltaTime);
}

void SceneManager::Render(D2DRenderer* _d2DRenderer)
{
	m_currentScene->Render(_d2DRenderer);
}

void SceneManager::DebugRender(D2DRenderer* _d2DRenderer)
{
	m_currentScene->DubugRender(_d2DRenderer);
}

void SceneManager::ProcessEvent(float _deltaTime)
{
	m_currentScene->ProcessEvent(_deltaTime);
}