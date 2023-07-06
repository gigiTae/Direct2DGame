#pragma once

#include "Manager.h"

class SceneManager;

class UIManager : public Manager
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

