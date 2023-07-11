
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

	// AABBTree 생성 
	m_aabbTree = new AABBTree(30.f,this);
}

void CollisionManager::Finalize()
{

	// 메모리 해제
	delete m_aabbTree;
}

void CollisionManager::DebugRender(D2DRenderer* _d2DRenderer)
{
	m_aabbTree->DebugRender(_d2DRenderer);
}

void CollisionManager::Update()
{
	// 새로추가된 콜라이더를 AABBTree에 추가는 오브젝트가 담당하는 하자 
	
	// AABBTree 삭제예정인 오브젝트, 확장한 사각형을 벗어난경우 처리
	m_aabbTree->Update();

	// 충돌한 콜라이더 pairList를 받아온다 
	ColliderPairList& pairList = m_aabbTree->ComputePairs();

	//받아온 Pair정보를 맵으로 정보를 갱신 
	for (auto& colldierPair : pairList)
	{
		ColliderKey key(colldierPair.first, colldierPair.second);
		
		auto iter = m_collisionInfomations.find(key);
		
		// 새로운 정보 삽입
		if (iter == m_collisionInfomations.end())
		{
			// 이전프레임 전프레임 충돌하지 않음 설정
			CollisionInfomation info = { false,true };
			m_collisionInfomations.insert(std::make_pair(key, std::move(info)));
		}
		else 
		{
			// 이번 프레임 충돌
			iter->second.currentCollision = true;
		}
	}

	// 오브젝트에게 충돌 이벤트 호출
	for (auto& iter : m_collisionInfomations)
	{
		Collision c1{};
		c1.otherCollider = iter.first.collider2;
		c1.otherObject = iter.first.collider2->GetGameObject();

		Collision c2{};
		c2.otherCollider = iter.first.collider1;
		c2.otherObject = iter.first.collider1->GetGameObject();

		if (iter.second.currentCollision)
		{
			if (iter.second.prevCollision)
			{
				// Stay
				iter.first.collider1->OnCollisionStay(c1);
				iter.first.collider2->OnCollisionStay(c2);
			}
			else
			{
				// Enter
				iter.first.collider1->OnCollisionEnter(c1);
				iter.first.collider2->OnCollisionEnter(c2);
			}
		}
		else
		{
			if (iter.second.prevCollision)
			{
				// Exit
					// Enter
				iter.first.collider1->OnCollisionExit(c1);
				iter.first.collider2->OnCollisionExit(c2);
			}
		}

		iter.second.prevCollision = iter.second.currentCollision;
		iter.second.currentCollision = false;
	}

}

void CollisionManager::CheckCollisionObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right) const
{
	// 비트 연산자를 통해서 그룹간의 충돌정보를 관리한다.
	m_collisionCheck[static_cast<int>(_left)] |= (1 << static_cast<int>(_right));
	m_collisionCheck[static_cast<int>(_right)] |= (1 << static_cast<int>(_left));
}

void CollisionManager::AddColider(Collider* _collider) const
{
	m_aabbTree->Add(_collider);
}

bool CollisionManager::IsCollision(Collider* _left, Collider* _right)
{
	OBJECT_TYPE left = _left->GetGameObject()->GetObjectType();
	OBJECT_TYPE right = _right->GetGameObject()->GetObjectType();

	int min = FMath::Min(static_cast<int>(left), static_cast<int>(right));
	int max = FMath::Max(static_cast<int>(left), static_cast<int>(right));

	if (m_collisionCheck[min] & (1 << max))
		return true;

	return false;
}
