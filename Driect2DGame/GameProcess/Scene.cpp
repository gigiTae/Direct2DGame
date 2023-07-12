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

	/// 랜더링은 부모 오브가 자식 오브젝트의 랜더링까지 담당한다.
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
	/// 씬변경 이벤트
	if (m_nextScene != SCENE_TYPE::NONE)
	{
		m_scneneManager->ChangeScene(m_nextScene);
		return;
	}

	/// 오브젝트 삭제관리 
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

	/// 오브젝트 추가 관리 
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
	/// 추가해야하는 오브젝트 정보
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

	/// 추가하는 오브젝트 목록 초기화
	for (auto& info : m_addObjectList)
	{
		GameObject* object = info.object;
		if (object != nullptr)
		{
			delete object;
		}
	}
	m_addObjectList.clear();

	// 다음씬 지정 해제
	m_nextScene = SCENE_TYPE::NONE;
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
	const PathManager* pathManager = m_managerSet->GetPathManager();

	wstring parentFilePath = pathManager->GetRelativPath();

	parentFilePath += L"\\Resource\\" + _sceneName;

	FileManager::GetFileMemberPath(filesPath, parentFilePath, false);
	FileManager::GetFileMemberName(fileName, parentFilePath, false);

	assert(filesPath.size() == fileName.size()); 

	/// 확장자명 제거하고 Key값으로 만들기  ex) apple.png -> apple
	for (int i = 0; i < static_cast<int>(fileName.size()); ++i)
	{
		while (true)
		{
			wchar_t tmp = fileName[i].back();
			fileName[i].pop_back();
			
			if (tmp == L'.') break;

			/// 확장자명을 확인해야할 필요가 있을듯
			assert(fileName.size() != 0 || !L"파일의 확장자 키워드가 없습니다.");
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
		
		/// 충돌체를 가지는 경우에는 충돌매니저의 트리에 충돌체를 추가한다.
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
	
	// 배열 초기화
	m_objectVector[static_cast<int>(_type)].clear();
}
