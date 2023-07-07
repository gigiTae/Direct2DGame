#pragma once


class GameObject;
class SceneManager;
class ManagerSet;

/// <summary>
///  UI���� ���콺 �Է� �̺�Ʈ�� �����ϴ� �Ŵ���
/// UI���� ������ �������
/// </summary>
class UIManager 
{
public:
	UIManager();
	~UIManager();

	void Initalize(SceneManager* _sceneManager, ManagerSet* _managerSet);
	void Update();
	void Finalize();

private:
	GameObject* GetFocusedUI();
	GameObject* GetTargetedUI(GameObject* _parent);

private:
	GameObject* m_foucsedUI; // ���� ��Ŀ�� ���� ������Ʈ
	SceneManager* m_sceneManager;
	ManagerSet* m_managerSet;
};

