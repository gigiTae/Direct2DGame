#include "GameProcessPCH.h"
#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
	:m_inputManager(nullptr)
	,m_sceneManager(nullptr)
	,m_collisionManager(nullptr)
	,m_objectVector{}
{
}

Scene::~Scene()
{
}

void Scene::Initalize(SceneManager* _sceneManager, InputManager* _inputManager, CollisionManager* _collisionManager)
{
	m_sceneManager = _sceneManager;
	m_inputManager = _inputManager;
	m_collisionManager = _collisionManager;
}

void Scene::Finalize()
{
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		DestoryGroupObject(static_cast<OBJECT_TYPE>(i)); 
	}
}

void Scene::Render(D2DRenderer* _d2DRenderer)
{
	assert(_d2DRenderer);

	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			iter->PreRender(_d2DRenderer);
		}
	}

	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			iter->Render(_d2DRenderer);
		}
	}

	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			iter->PostRender(_d2DRenderer);
		}
	}
}

void Scene::ProcessEvent()
{
	/// 오브젝트 삭제관리 // 점점 게임프로세스가 무거워지는데 괜찮은가? 
	/// 오브젝트 풀링도 고민해봐야?
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		auto iter = m_objectVector[i].begin();

		while (iter != m_objectVector[i].end())
		{
			OBJECT_STATE state = (*iter)->GetObjectState();

			if (state == OBJECT_STATE::DESTORY)
			{
				// 오브젝트 삭제처리
				(*iter)->Finalize();
				delete (*iter);
				iter = m_objectVector->erase(iter);
			}
			else 
			{
				if (state == OBJECT_STATE::TO_BE_DESTORYED && (*iter)->GetDestroyTime() <= 0.f)
				{
					// 다음 프레임이 오브젝트 메모리 해제
					(*iter)->SetObjectState(OBJECT_STATE::DESTORY);
				}
				++iter;
			}
		}

	}

}

void Scene::DubugRender(D2DRenderer* _d2DRenderer)
{
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			iter->DebugRender(_d2DRenderer);
		}
	}
}

void Scene::FixedUpdate(float _fixedDeltaTime)
{
	assert(m_inputManager);

	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			iter->FixedUpdate(_fixedDeltaTime, m_inputManager);
		}
	}


	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			iter->IntergrateForces(_fixedDeltaTime);
		}
	}
}

void Scene::Update(float _deltaTime)
{
	assert(m_inputManager);

	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			iter->Update(_deltaTime,m_inputManager);
		}
	}
}

void Scene::LateUpdate(float _deltaTime)
{
	assert(m_inputManager);

	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			iter->LateUpdate(_deltaTime,m_inputManager);
		}
	}
}

void Scene::AddObject(GameObject* _object, OBJECT_TYPE _type)
{
	m_objectVector[static_cast<int>(_type)].push_back(_object);
}

void Scene::DestoryGroupObject(OBJECT_TYPE _type)
{ 
	for (auto iter : m_objectVector[static_cast<int>(_type)])
	{
		iter->Finalize();
		delete iter;
	}
}
