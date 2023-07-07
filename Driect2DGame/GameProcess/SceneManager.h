#pragma once

class GameObject;
class InputManager;
class SceneManager;
class ManagerSet;
class Scene;

/// <summary>
/// 씬을 관리해주는 매니져 
///   
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Initalize(D2DRenderer* _d2DRenderer, ManagerSet* _managerSet,SceneManager* _sceneManager);
	void Finalize();

	/// 이벤트 관련
	void FixedUpdate(float _fiexedDeltaTime);
	void Update(float _deltaTime);
	void LateUpdate(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer);
	void DebugRender(D2DRenderer* _d2DRenderer);
	void ProcessEvent(float _deltaTime);

	Scene* GetCurrentScene() { return m_currentScene; }
	void ChangeScene(SCENE_TYPE _nextScene);

	void RegisterObject(GameObject* _object, OBJECT_TYPE _type, float _delayTime) const;
	void RegisterNextScene(SCENE_TYPE _nextScene)const;

	bool IsGameRun() { return m_gameRun; }

private:
	D2DRenderer* m_d2DRenderer;
	ManagerSet* m_managerSet;
	bool m_gameRun; 

	// 모든 씬들을 관리
	Scene* m_sceneList[static_cast<int>(SCENE_TYPE::END)];
	Scene* m_currentScene;
};

