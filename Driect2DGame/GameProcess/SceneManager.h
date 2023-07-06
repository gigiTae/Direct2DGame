#pragma once

#include "Manager.h"

class Scene;
class InputManager;
class CollisionManager;
class ManagerSet;
/// <summary>
/// ���� �������ִ� �Ŵ��� 
///   
/// </summary>
class SceneManager : public Manager
{
public:
	SceneManager();
	~SceneManager();


	void Initalize(D2DRenderer* _d2DRenderer, ManagerSet* _managerSet);
	void Finalize();

	/// �̺�Ʈ ����
	void FixedUpdate(float _fiexedDeltaTime);
	void Update(float _deltaTime);
	void LateUpdate(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer);
	void DebugRender(D2DRenderer* _d2DRenderer);
	void ProcessEvent();

	const Scene* GetCurrentScene() const{ return m_currentScene; }
	void ChangeScene(SCENE_TYPE _nextScene);

	bool IsGameRun() { return m_gameRun; }

private:
	D2DRenderer* m_d2DRenderer;
	ManagerSet* m_managerSet;

	bool m_gameRun; 

	// ��� ������ ����
	Scene* m_sceneList[static_cast<int>(SCENE_TYPE::END)];
	Scene* m_currentScene;
};

