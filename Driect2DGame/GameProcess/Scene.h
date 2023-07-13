#pragma once

// ���漱��
class GameObject;
class ManagerSet;
class SceneManager;

struct AddObjectInfomation
{
	GameObject* object;
	float delayTime;
};

/// <summary>
/// ���� �����ϴ� �������̽��̴� 
/// ���� �����ϱ����� Enter�Լ��� ���ؼ� ������Ʈ���� �߰��ϰ� �������� ����
/// </summary>
class Scene abstract
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void Initalize(D2DRenderer* _d2DRenderer, ManagerSet* _managerSet, SceneManager* _sceneManager);
	virtual void Finalize();

	// ���� �������� ȣ���ϴ� �Լ�
	virtual void Enter() = 0;
	// ���� ���������� ȣ���ϴ� �Լ�
	virtual void Exit();

protected:
	// ���� �������� �ʿ��� ���ҽ����� �ε��Ѵ�.
	void LoadSceneResources(const wstring& _sceneName);

public:
	void FixedUpdate(float _fixedDeltaTime);
	void Update(float deltaTime);
	void LateUpdate(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer);
	void DubugRender(D2DRenderer* _d2DRenderer);
	
	//�ļ� �̺�Ʈ ó��
	void ProcessEvent(float _deltaTime);
public: 

	/// ���� ������Ʈ �߰��� ��û
	void RegisterObject(GameObject* _object, float _delayTime)const;
	void RegisterNextScene(SCENE_TYPE _nextScene) const;

	const vector<GameObject*>& GetGroupObject(OBJECT_TYPE _type) const  
	{ return m_objectVector[static_cast<int>(_type)]; }

	vector<GameObject*>& GetUIGroupObject(OBJECT_TYPE _type) 
	{
		if (_type == OBJECT_TYPE::BACK_UI || _type == OBJECT_TYPE::FRONT_UI)
			return m_objectVector[static_cast<int>(_type)];
		else
		{
			assert(nullptr);
			return m_objectVector[static_cast<int>(_type)];
		}
	}

protected:
	/// �ڽĿ�����Ʈ�鵵 ���� ���
	void AddObject(GameObject* _object); 
	void DestoryGroupObject(OBJECT_TYPE _type);
	const ManagerSet* GetManagerSet() { return m_managerSet; }

private:
	SceneManager* m_scneneManager;
	D2DRenderer* m_d2DRenderer;
	ManagerSet* m_managerSet;

	// ���ҽ����� �ε��ߴ���
	bool m_loadResources;

	// ���� ������Ʈ Ÿ�Կ� ���� ������Ʈ���� �����Ѵ�.
	vector<GameObject*> m_objectVector[static_cast<int>(OBJECT_TYPE::END)];
	// �������� Ÿ���� ������ NONEŸ���̸� �������� ����
	mutable SCENE_TYPE m_nextScene;
	// ���� �߰��ؾ��ϴ� ������Ʈ���� �߰��ϴ� �ð��� �Բ� ������ �ִ´�.
	mutable list<AddObjectInfomation> m_addObjectList;

};

