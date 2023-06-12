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
	assert(_d2DRenderer);

	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectList[i])
		{
			iter->Render(_d2DRenderer);

			iter->ComponentRender(_d2DRenderer);
		}
	}
}

void Scene::Update(float _deltaTime)
{
	assert(m_inputManager);

	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectList[i])
		{
			iter->Update(_deltaTime,m_inputManager);
		}
	}
}

void Scene::FinalUpdate(float _deltaTime)
{
	assert(m_inputManager);

	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectList[i])
		{
			iter->FinalUpdate(_deltaTime);
		}
	}
}

void Scene::AddObject(GameObject* _object, OBJECT_TYPE _type)
{
	m_objectList[static_cast<int>(_type)].push_back(_object);

}
