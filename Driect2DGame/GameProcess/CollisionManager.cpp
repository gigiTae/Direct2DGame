
#include"GameProcessPCH.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "AABBTree.h"
#include "Scene.h"

CollisionManager::CollisionManager()
	:m_inputManager(nullptr)
	,m_sceneManager(nullptr)
	,m_collisionCheck{}
	,m_aabbTree(nullptr)
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Initalize(InputManager* _inputManager, SceneManager* _sceneManager)
{
	m_inputManager = _inputManager;
	m_sceneManager = _sceneManager;

	// AABBTree ���� 
	m_aabbTree = new AABBTree(10.f,this);
}

void CollisionManager::Finalize()
{

	// �޸� ����
	delete m_aabbTree;
}

void CollisionManager::Update()
{
	// �����߰��� �ݶ��̴��� AABBTree�� �߰��� ������Ʈ�� ����ϴ� ���� 
	
	// AABBTree ���������� ������Ʈ, Ȯ���� �簢���� ������ ó��
	m_aabbTree->Update();

	// �浹�� �ݶ��̴� pairList�� �޾ƿ´� 
	ColliderPairList& pairList = m_aabbTree->ComputePairs();

	// ������Ʈ���� �浹 �̺�Ʈ ȣ��
	

}

void CollisionManager::CheckCollisionObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right) const
{
	// ��Ʈ �����ڸ� ���ؼ� �׷찣�� �浹������ �����Ѵ�.
	m_collisionCheck[static_cast<int>(_left)] |= (1 << static_cast<int>(_right));
	m_collisionCheck[static_cast<int>(_right)] |= (1 << static_cast<int>(_left));
}

void CollisionManager::AddColider(Collider* _collider) const
{
	m_aabbTree->Add(_collider);
}

bool CollisionManager::IsCollisionType(OBJECT_TYPE _left, OBJECT_TYPE _right)
{
	int min = FMath::Min(static_cast<int>(_left), static_cast<int>(_right));
	int max = FMath::Max(static_cast<int>(_left), static_cast<int>(_right));

	if (m_collisionCheck[min] & (1 << max))
		return true;

	return false;
}
