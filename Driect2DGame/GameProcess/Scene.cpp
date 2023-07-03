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
	/// ������Ʈ �������� // ���� �������μ����� ���ſ����µ� ��������? 
	/// ������Ʈ Ǯ���� ����غ���?
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		auto iter = m_objectVector[i].begin();

		while (iter != m_objectVector[i].end())
		{
			GameObject* object = (*iter);
			OBJECT_STATE state = object->GetObjectState();

			if (state == OBJECT_STATE::DESTORY)
			{
				// ������Ʈ ����ó��
				object->Finalize();
				delete object;
				iter = m_objectVector[i].erase(iter);
			}
			else 
			{
				if (state == OBJECT_STATE::TO_BE_DESTORYED && object->GetDestroyTime() <= 0.f)
				{
					// ���� �������� ������Ʈ �޸� ����
					// �ڽ� ������Ʈ�鸸 �����Ѵ�, �θ�� �������� �ʴ´�.
					queue<GameObject*> q;
					q.push(object);
					while (!q.empty())
					{
						GameObject* tmp = q.front();
						tmp->SetObjectState(OBJECT_STATE::DESTORY);
						
						vector<GameObject*>& children = tmp->GetChildren();
						for (int i = 0; i < static_cast<int>(children.size()); ++i)
						{
							q.push(children[i]);
						}
						q.pop();
					}
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

void Scene::Exit()
{
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		DestoryGroupObject(static_cast<OBJECT_TYPE>(i));
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
	queue<GameObject*> q;
	q.push(_object);

	while (!q.empty())
	{
		GameObject* tmp = q.front();
		m_objectVector[static_cast<int>(_type)].push_back(tmp);

		for (auto child : tmp->GetChildren())
		{
			q.push(child);
		}

		q.pop();
	}
}

void Scene::DestoryGroupObject(OBJECT_TYPE _type)
{ 
	for (auto iter : m_objectVector[static_cast<int>(_type)])
	{
		iter->Finalize();
		delete iter;
	}
}
