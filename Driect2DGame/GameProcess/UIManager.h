#pragma once



class SceneManager;

class UIManager 
{
public:
	UIManager();
	~UIManager();

	void Initalize(SceneManager* _sceneManager);
	void Update();
	void Finalize();

private:
	SceneManager* m_sceneManager;

};

