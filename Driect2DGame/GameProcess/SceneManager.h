#pragma once

class Scene;
class InputManager;
class CollisionManager;
/// <summary>
/// 씬을 관리해주는 매니져 
/// 조금씩 크기가 커질거같음?
///   
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Initalize(InputManager* _inputManager, CollisionManager* _collisionManager);
	void Finalize();
	
	/// 이벤트 관련
	void FixedUpdate(float _fiexedDeltaTime);
	void Update(float _deltaTime);
	void LateUpdate(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer);
	void DebugRender(D2DRenderer* _d2DRenderer);
	void ProcessEvent();

	Scene* GetCurrentScene() { return m_currentScene; }
	void ChangeScene(SCENE_TYPE _nextScene);

private:
	// 모든 씬들을 관리
	Scene* m_sceneList[static_cast<int>(SCENE_TYPE::END)];
	Scene* m_currentScene;
};

