#pragma once

// ���漱��
class GameObject;
class InputManager;
class CollisionManager;

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	InputManager* GetInputManager() { return m_inputManager; }

public:
	virtual void Initalize(InputManager* _inputManager, CollisionManager* _collisionManager);
	virtual void Finalize();

	// ���� �������� ȣ���ϴ� �Լ�
	virtual void Enter() = 0;

	// ���� ���������� ȣ���ϴ� �Լ�
	virtual void Exit() = 0;

	virtual void Render(D2DRenderer* _d2DRenderer);
	virtual void FixedUpdate(float _fixedDeltaTime);
	virtual void Update(float deltaTime);
	virtual void FinalUpdate(float _deltaTime);

	const vector<GameObject*>& GetGroupObject(OBJECT_TYPE _type) 
	{ return m_objectVector[static_cast<int>(_type)]; }


protected:
	void AddObject(GameObject* _object, OBJECT_TYPE _type);
	void DestoryGroupObject(OBJECT_TYPE _type);

protected:
	CollisionManager* GetCollisionManager() { return m_collisionManager; }
private:
	InputManager* m_inputManager;
	CollisionManager* m_collisionManager;

	// ���� ������Ʈ Ÿ�Կ� ���� ������Ʈ���� �����Ѵ�.
	vector<GameObject*> m_objectVector[static_cast<int>(OBJECT_TYPE::END)];
};

