#include "GameProcessPCH.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ManagerSet.h"
#include "InputManager.h"

UIManager::UIManager()
	:m_sceneManager(nullptr)
	,m_foucsedUI(nullptr)
	,m_managerSet(nullptr)
{}

UIManager::~UIManager()
{

}
void UIManager::Initalize(SceneManager* _sceneManager, ManagerSet* _managerSet)
{
	m_sceneManager = _sceneManager;
	m_managerSet = _managerSet;
}

void UIManager::Update()
{
	/// ���� ��Ŀ�� ���� UI Ȯ��
	m_foucsedUI = GetFocusedUI();

	// ���� ��Ŀ�� ���� UI�� ���� ���
	if (!m_foucsedUI)
		return;

	const InputManager* input = m_managerSet->GetInputManager();

	GameObject* targetUI = GetTargetedUI(m_foucsedUI);

	if (targetUI == nullptr)
		return;

	bool leftAway = input->IsKeyState(KEY::LMOUSE, KEY_STATE::AWAY);
	bool leftTap = input->IsKeyState(KEY::LMOUSE, KEY_STATE::TAP);

}

void UIManager::Finalize()
{

}

GameObject* UIManager::GetFocusedUI()
{
	return nullptr;
}

GameObject* UIManager::GetTargetedUI(GameObject* _parent)
{
	return nullptr;
}
