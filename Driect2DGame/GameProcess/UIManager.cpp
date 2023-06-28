#include "GameProcessPCH.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "Scene.h"

UIManager::UIManager()
	:m_sceneManager(nullptr)
{}

UIManager::~UIManager()
{

}

void UIManager::Initalize(SceneManager* _sceneManager)
{
	m_sceneManager = _sceneManager;
}

void UIManager::Update()
{
	Scene* currentScene = m_sceneManager->GetCurrentScene();
	
	 
}

void UIManager::Finalize()
{

}
