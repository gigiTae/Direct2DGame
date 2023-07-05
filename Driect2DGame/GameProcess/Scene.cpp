#include "GameProcessPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "PathManager.h"
#include "FileManager.h"

Scene::Scene()
	:m_inputManager(nullptr)
	,m_sceneManager(nullptr)
	,m_d2DRenderer(nullptr)
	,m_collisionManager(nullptr)
	,m_objectVector{}
	,m_loadResources(false)
{
}

Scene::~Scene()
{
}

void Scene::Initalize(D2DRenderer* _d2DRenderer, SceneManager* _sceneManager, InputManager* _inputManager, CollisionManager* _collisionManager)
{
	m_d2DRenderer = _d2DRenderer;
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
			GameObject* object = (*iter);
			OBJECT_STATE state = object->GetObjectState();

			if (state == OBJECT_STATE::DESTORY)
			{
				// 오브젝트 삭제처리
				object->Finalize();
				delete object;
				iter = m_objectVector[i].erase(iter);
			}
			else 
			{
				if (state == OBJECT_STATE::TO_BE_DESTORYED && object->GetDestroyTime() <= 0.f)
				{
					// 다음 프레임이 오브젝트 메모리 해제
					// 자식 오브젝트들만 삭제한다, 부모는 삭제하지 않는다.
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

void Scene::LoadSceneResources(const wstring& _sceneName)
{
	/// 리소스를 한번이라도 로드한적이 있는지 
	if (m_loadResources)
	{
		return;
	}

	/// 리소스 파일로 경로를 연결한다
	vector<wstring> filesPath{}, fileName{};
	wstring parentFilePath = PathManager::GetRelativPath();
	parentFilePath += L"\\Resource\\" + _sceneName;

	FileManager::GetFileMemberPath(filesPath, parentFilePath, false);
	FileManager::GetFileMemberName(fileName, parentFilePath, false);

	assert(filesPath.size() == fileName.size()); 

	/// 확장자명 제거하고 Key값으로 만들기 
	for (int i = 0; i < static_cast<int>(fileName.size()); ++i)
	{
		while (true)
		{
			wchar_t tmp = fileName[i].back();
			fileName[i].pop_back();
			
			if (tmp == L'.') break;

			/// 확장자명을 확인해야할 필요가 있을듯
			assert(fileName.size() != 0);
		}
	}

	for (int i = 0; i < static_cast<int>(fileName.size()); ++i)
	{
		/// 파일 이름을 key값으로 사용한다
		m_d2DRenderer->LoadBitMap(fileName[i], filesPath[i].c_str());
	}

	m_loadResources = true;
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
