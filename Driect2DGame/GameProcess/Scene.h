#pragma once

// ���漱��
class GameObject;
class InputManager;

class Scene 
{
public:
	Scene();
	virtual ~Scene();

public:
	InputManager* GetInputManager() { return m_inputManager; }

public:
	virtual void Initalize(InputManager* _inputManager);
	virtual void Finalize() {};

	// ���� �������� ȣ���ϴ� �Լ�
	virtual void Enter() = 0;

	// ���� ���������� ȣ���ϴ� �Լ�
	virtual void Exit() = 0;

	virtual void Render(D2DRenderer* _d2DRenderer);
	virtual void Update(float deltaTime);
	virtual void FinalUpdate(float _deltaTime);

	void AddObject(GameObject* _object, OBJECT_TYPE _type);
private:
	InputManager* m_inputManager;

	// ���� ������Ʈ Ÿ�Կ� ���� ������Ʈ���� �����Ѵ�.
	vector<GameObject*> m_objectList[static_cast<int>(OBJECT_TYPE::END)];
};

