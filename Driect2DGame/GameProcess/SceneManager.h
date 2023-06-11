#pragma once

class Scene;
class InputManager;
/// <summary>
/// ���� �������ִ� �Ŵ��� 
/// ���ݾ� ũ�Ⱑ Ŀ���Ű���?
///   
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Initalize(InputManager* _inputManager);
	void Update(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer);
	void Finalize();

	Scene* GetCurrentScene() { return m_currentScene; }
	void ChangeScene(SCENE_TYPE _nextScene);

private:
	// ��� ������ ����
	Scene* m_sceneList[static_cast<int>(SCENE_TYPE::END)];
	Scene* m_currentScene;
};

