#pragma once

// ���漱��
class GameObject;
class ManagerSet;

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
	virtual void Initalize(D2DRenderer* _d2DRenderer, ManagerSet* _managerSet);
	virtual void Finalize();

	// ���� �������� ȣ���ϴ� �Լ�
	virtual void Enter() = 0;
	// ���� ���������� ȣ���ϴ� �Լ�
	virtual void Exit();

protected:
	// ���� �������� �ʿ��� ���ҽ����� �ε��Ѵ�.
	void LoadSceneResources(const wstring& _sceneName);
private:
	// ���ҽ����� �ε��ߴ���
	bool m_loadResources;

public:
	void FixedUpdate(float _fixedDeltaTime);
	void Update(float deltaTime);
	void LateUpdate(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer);
	void ProcessEvent();

	/// ����� ������ ������
	void DubugRender(D2DRenderer* _d2DRenderer);

	const vector<GameObject*>& GetGroupObject(OBJECT_TYPE _type) const  
	{ return m_objectVector[static_cast<int>(_type)]; }

protected:
	/// �ڽĿ�����Ʈ�鵵 ���� ���
	void AddObject(GameObject* _object, OBJECT_TYPE _type); 
	void AddObject(GameObject* _object, OBJECT_TYPE _type) const;
	void DestoryGroupObject(OBJECT_TYPE _type);
	const ManagerSet* GetManagerSet() { return m_managerSet; }

private:
	D2DRenderer* m_d2DRenderer;
	ManagerSet* m_managerSet;

	// ���� ������Ʈ Ÿ�Կ� ���� ������Ʈ���� �����Ѵ�.
	vector<GameObject*> m_objectVector[static_cast<int>(OBJECT_TYPE::END)];
};

