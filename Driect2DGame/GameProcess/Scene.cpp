#include "GameProcessPCH.h"
#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
	:m_inputManager(nullptr)
	,m_objectList{}
{
}

Scene::~Scene()
{
}

void Scene::Initalize(InputManager* _inputManager)
{
	m_inputManager = _inputManager;
}

void Scene::Render(D2DRenderer* _d2DRenderer)
{
}

void Scene::Update(float _deltaTime)
{
	assert(m_inputManager == nullptr);

	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		auto iter = m_objectList[i].begin();

		while (iter != m_objectList->end())
		{
			(*iter)->Update(_deltaTime, m_inputManager);
		}
	}
}
