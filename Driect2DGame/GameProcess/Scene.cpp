#include "GameProcessPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "PathManager.h"
#include "FileManager.h"
#include "ManagerSet.h"
#include "SceneManager.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "CollisionManager.h"

Scene::Scene()
	:m_d2DRenderer(nullptr)
	,m_managerSet(nullptr)
	,m_objectVector{}
	,m_loadResources(false)
	,m_nextScene(SCENE_TYPE::NONE)
	,m_addObjectList{}
	,m_scneneManager(nullptr)
{
}

Scene::~Scene()
{
}

void Scene::Initalize(D2DRenderer* _d2DRenderer, ManagerSet* _managerSet, SceneManager* _sceneManager)
{
	m_scneneManager = _sceneManager;
	m_managerSet = _managerSet;
	m_d2DRenderer = _d2DRenderer;
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

	/// �������� �θ� ���갡 �ڽ� ������Ʈ�� ���������� ����Ѵ�.
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			bool isCameraAffectedObject = iter->IsCameraAffected();

			_d2DRenderer->SetCameraAffected(isCameraAffectedObject);

			if (iter->GetParent() == nullptr)
			{
				iter->PreRender(_d2DRenderer);
				iter->Render(_d2DRenderer);
				iter->PostRender(_d2DRenderer);
			}
		}
	}
}

void Scene::ProcessEvent(float _deltaTime)
{
	/// ������ �̺�Ʈ
	if (m_nextScene != SCENE_TYPE::NONE)
	{
		m_scneneManager->ChangeScene(m_nextScene);
		return;
	}

	/// ������Ʈ �������� 
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

	/// ������Ʈ �߰� ���� 
	auto iter = m_addObjectList.begin();

	while (iter != m_addObjectList.end())
	{
		iter->delayTime -= _deltaTime;
		if (iter->delayTime <= 0.f)
		{
			AddObject(iter->object, iter->type);
			iter = m_addObjectList.erase(iter);
		}
		else
			++iter;
	}
}

void Scene::RegisterObject(GameObject* _object, OBJECT_TYPE _type, float _delayTime) const
{
	/// �߰��ؾ��ϴ� ������Ʈ ����
	AddObjectInfomation info{};
	info.type = _type;
	info.delayTime = _delayTime;
	info.object = _object;

	m_addObjectList.push_back(std::move(info));
}
 
void Scene::RegisterNextScene(SCENE_TYPE _nextScene) const
{
	m_nextScene = _nextScene;
}

void Scene::DubugRender(D2DRenderer* _d2DRenderer)
{
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			bool isCameraAffectedObject = iter->IsCameraAffected();

			_d2DRenderer->SetCameraAffected(isCameraAffectedObject);

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

	/// �߰��ϴ� ������Ʈ ��� �ʱ�ȭ
	for (auto& info : m_addObjectList)
	{
		GameObject* object = info.object;
		if (object != nullptr)
		{
			delete object;
		}
	}
	m_addObjectList.clear();

	// ������ ���� ����
	m_nextScene = SCENE_TYPE::NONE;
}

void Scene::LoadSceneResources(const wstring& _sceneName)
{
	/// ���ҽ��� �ѹ��̶� �ε������� �ִ��� 
	if (m_loadResources)
	{
		return;
	}

	/// ���ҽ� ���Ϸ� ��θ� �����Ѵ�
	vector<wstring> filesPath{}, fileName{};
	const PathManager* pathManager = m_managerSet->GetPathManager();

	wstring parentFilePath = pathManager->GetRelativPath();

	parentFilePath += L"\\Resource\\" + _sceneName;

	FileManager::GetFileMemberPath(filesPath, parentFilePath, false);
	FileManager::GetFileMemberName(fileName, parentFilePath, false);

	assert(filesPath.size() == fileName.size()); 

	/// Ȯ���ڸ� �����ϰ� Key������ �����  ex) apple.png -> apple
	for (int i = 0; i < static_cast<int>(fileName.size()); ++i)
	{
		while (true)
		{
			wchar_t tmp = fileName[i].back();
			fileName[i].pop_back();
			
			if (tmp == L'.') break;

			/// Ȯ���ڸ��� Ȯ���ؾ��� �ʿ䰡 ������
			assert(fileName.size() != 0 || !L"������ Ȯ���� Ű���尡 �����ϴ�.");
		}
	}

	for (int i = 0; i < static_cast<int>(fileName.size()); ++i)
	{
		/// ���� �̸��� key������ ����Ѵ�
		m_d2DRenderer->LoadBitMap(fileName[i], filesPath[i].c_str());
	}

	m_loadResources = true;
}

void Scene::FixedUpdate(float _fixedDeltaTime)
{

	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			iter->FixedUpdate(_fixedDeltaTime);
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
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			iter->Update(_deltaTime);
		}
	}
}

void Scene::LateUpdate(float _deltaTime)
{
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (auto iter : m_objectVector[i])
		{
			iter->LateUpdate(_deltaTime);
		}
	}
}

void Scene::AddObject(GameObject* _object, OBJECT_TYPE _type)
{
	queue<GameObject*> q;
	q.push(_object);

	const CollisionManager* collisionMgr = m_managerSet->GetCollisionManager();


	while (!q.empty())
	{
		GameObject* tmp = q.front();
		m_objectVector[static_cast<int>(_type)].push_back(tmp);
		
		/// �浹ü�� ������ ��쿡�� �浹�Ŵ����� Ʈ���� �浹ü�� �߰��Ѵ�.
		BoxCollider* box = tmp->GetComponent<BoxCollider>();
		CircleCollider* circle = tmp->GetComponent<CircleCollider>();

		if (box != nullptr)
		{
			collisionMgr->AddColider(box);
		}
		if (circle != nullptr)
		{
			collisionMgr->AddColider(circle);
		}

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
	
	// �迭 �ʱ�ȭ
	m_objectVector[static_cast<int>(_type)].clear();
}
