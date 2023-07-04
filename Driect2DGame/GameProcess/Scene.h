#pragma once

// 전방선언
class GameObject;
class InputManager;
class SceneManager;
class CollisionManager;

/// <summary>
/// 씬을 구성하는 인터페이스이다 
/// 씬에 입장하기전에 Enter함수를 통해서 오브젝트들을 추가하고 여러가지 설정
/// </summary>
class Scene abstract
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void Initalize(D2DRenderer* _d2DRenderer
		,SceneManager* _sceneManager,InputManager* _inputManager, CollisionManager* _collisionManager);
	virtual void Finalize();

	// 씬에 들어가지전에 호출하는 함수
	virtual void Enter() = 0;
	// 씬에 나가기전에 호출하는 함수
	virtual void Exit();

protected:
	// 씬에 들어가기전에 필요한 리소스들을 로드한다.
	void LoadSceneResources(const wstring& _sceneName);
private:
	// 리소스들을 로드했는지
	bool m_loadResources;

public:
	void FixedUpdate(float _fixedDeltaTime);
	void Update(float deltaTime);
	void LateUpdate(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer);
	void ProcessEvent();

	/// 디버그 정보를 랜더링
	void DubugRender(D2DRenderer* _d2DRenderer);

	const vector<GameObject*>& GetGroupObject(OBJECT_TYPE _type) 
	{ return m_objectVector[static_cast<int>(_type)]; }

protected:
	/// 자식오브젝트들도 같이 등록
	void AddObject(GameObject* _object, OBJECT_TYPE _type); 
	void DestoryGroupObject(OBJECT_TYPE _type);

protected:
	CollisionManager* GetCollisionManager() { return m_collisionManager; }
private:

	D2DRenderer* m_d2DRenderer;

	SceneManager* m_sceneManager;
	InputManager* m_inputManager;
	CollisionManager* m_collisionManager;

	// 씬이 오브젝트 타입에 따라서 오브젝트들을 관리한다.
	vector<GameObject*> m_objectVector[static_cast<int>(OBJECT_TYPE::END)];
};

