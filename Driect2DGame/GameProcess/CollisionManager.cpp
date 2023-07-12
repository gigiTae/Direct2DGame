
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
	m_aabbTree = new AABBTree(25.f,this);
}

void CollisionManager::Finalize()
{

	// �޸� ����
	delete m_aabbTree;
}

void CollisionManager::DebugRender(D2DRenderer* _d2DRenderer)
{
	m_aabbTree->DebugRender(_d2DRenderer);
}

void CollisionManager::Update()
{
	// �����߰��� �ݶ��̴��� AABBTree�� �߰��� ������Ʈ�� ����Ѵ� 

	// AABBTree ���������� ������Ʈ, Ȯ���� �簢���� ������ ó��
	m_aabbTree->Update();

	// �浹�� �ݶ��̴� pairList�� �޾ƿ´� 
	ColliderPairList& pairList = m_aabbTree->ComputePairs();

	//�޾ƿ� Pair������ ������ ������ ���� 
	for (auto& colldierPair : pairList)
	{
		ColliderKey key(colldierPair.first, colldierPair.second);

		auto iter = m_collisionInfomations.find(key);

		// ���ο� ���� ����
		if (iter == m_collisionInfomations.end())
		{
			// ���������� �������� �浹���� ���� ����
			CollisionInfomation info = { colldierPair.first
				,colldierPair.second
				,false,true };
			m_collisionInfomations.insert(std::make_pair(key, std::move(info)));
		}
		else
		{
			// �̹� ������ �浹
			iter->second.currentCollision = true;
		}
	}

	// ������Ʈ���� �浹 �̺�Ʈ ȣ��
	for (auto& iter : m_collisionInfomations)
	{
		Collision c1{};
		c1.otherCollider = iter.second.collider2;
		c1.otherObject = iter.second.collider2->GetGameObject();

		Collision c2{};
		c2.otherCollider = iter.second.collider1;
		c2.otherObject = iter.second.collider1->GetGameObject();

		if (iter.second.currentCollision)
		{
			if (iter.second.prevCollision)
			{
				// Stay
				iter.second.collider1->OnCollisionStay(c1);
				iter.second.collider2->OnCollisionStay(c2);
			}
			else
			{
				// Enter
				iter.second.collider1->OnCollisionEnter(c1);
				iter.second.collider2->OnCollisionEnter(c2);
			}
		}
		else
		{
			if (iter.second.prevCollision)
			{
				// Exit
				iter.second.collider1->OnCollisionExit(c1);
				iter.second.collider2->OnCollisionExit(c2);
			}
		}

		iter.second.prevCollision = iter.second.currentCollision;
		iter.second.currentCollision = false;
	}

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

void CollisionManager::Clear()
{
	m_collisionInfomations.clear();
	m_aabbTree->Clear();
}

bool CollisionManager::IsCollision(Collider* _left, Collider* _right)
{
	OBJECT_TYPE left = _left->GetGameObject()->GetObjectType();
	OBJECT_TYPE right = _right->GetGameObject()->GetObjectType();

	int leftIndex = static_cast<int>(left);
	int rightIndex = static_cast<int>(right);

	if (m_collisionCheck[leftIndex] & (1 << rightIndex))
		return true;

	return false;
}
