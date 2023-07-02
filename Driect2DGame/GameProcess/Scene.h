#pragma once

// ���漱��
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

	// ���� �������� ȣ���ϴ� �Լ�
	virtual void Enter() = 0;

	// ���� ���������� ȣ���ϴ� �Լ�
	virtual void Exit() = 0;

	void FixedUpdate(float _fixedDeltaTime);
	void Update(float deltaTime);
	void LateUpdate(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer);
	void ProcessEvent();

	/// ����� ������ ������
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

	// ���� ������Ʈ Ÿ�Կ� ���� ������Ʈ���� �����Ѵ�.
	vector<GameObject*> m_objectVector[static_cast<int>(OBJECT_TYPE::END)];
};

