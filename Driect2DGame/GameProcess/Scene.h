#pragma once

// 전방선언
class GameObject;
class InputManager;
class SceneManager;
class CollisionManager;

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void Initalize(SceneManager* _sceneManager,InputManager* _inputManager, CollisionManager* _collisionManager);
	virtual void Finalize();

	// 씬에 들어가지전에 호출하는 함수
	virtual void Enter() = 0;

	// 씬에 나가기전에 호출하는 함수
	virtual void Exit() = 0;

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
	void AddObject(GameObject* _object, OBJECT_TYPE _type); 
	void DestoryGroupObject(OBJECT_TYPE _type);

protected:
	CollisionManager* GetCollisionManager() { return m_collisionManager; }
private:
	SceneManager* m_sceneManager;
	InputManager* m_inputManager;
	CollisionManager* m_collisionManager;

	// 씬이 오브젝트 타입에 따라서 오브젝트들을 관리한다.
	vector<GameObject*> m_objectVector[static_cast<int>(OBJECT_TYPE::END)];
};

