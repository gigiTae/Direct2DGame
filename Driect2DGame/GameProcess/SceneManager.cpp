#include "GameProcessPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "MainScene.h"
#include "InputManager.h"

SceneManager::SceneManager()
	:m_currentScene(nullptr)
	,m_sceneList{}
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initalize(InputManager* _inputManager)
{
	// 씬 메모리 공간할당
	m_sceneList[static_cast<int>(SCENE_TYPE::MAIN)] = new MainScene();

	// 씬 명시적 초기화

	m_sceneList[static_cast<int>(SCENE_TYPE::MAIN)]->Initalize(_inputManager);

	// 현재씬을 지정한다
	m_currentScene = m_sceneList[static_cast<int>(SCENE_TYPE::MAIN)];

	m_currentScene->Enter();
}

void SceneManager::Update(float _deltaTime)
{
	m_currentScene->Update(_deltaTime);
}

void SceneManager::FinalUpdate(float _deltaTime)
{
	m_currentScene->FinalUpdate(_deltaTime);
}

void SceneManager::Render(D2DRenderer* _d2DRenderer)
{
	m_currentScene->Render(_d2DRenderer);
}

void SceneManager::Finalize()
{
}

void SceneManager::ChangeScene(SCENE_TYPE _nextScene)
{
	m_currentScene->Exit();

	m_currentScene = m_sceneList[static_cast<int>(_nextScene)];

	m_currentScene->Enter();
}
