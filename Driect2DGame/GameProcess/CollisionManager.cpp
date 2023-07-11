
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
	m_aabbTree = new AABBTree(10.f,this);
}

void CollisionManager::Finalize()
{

	// 메모리 해제
	delete m_aabbTree;
}

void CollisionManager::Update()
{
	// 새로추가된 콜라이더를 AABBTree에 추가는 오브젝트가 담당하는 하자 
	
	// AABBTree 삭제예정인 오브젝트, 확장한 사각형을 벗어난경우 처리
	m_aabbTree->Update();

	// 충돌한 콜라이더 pairList를 받아온다 
	ColliderPairList& pairList = m_aabbTree->ComputePairs();

	// 오브젝트에게 충돌 이벤트 호출
	

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

bool CollisionManager::IsCollisionType(OBJECT_TYPE _left, OBJECT_TYPE _right)
{
	int min = FMath::Min(static_cast<int>(_left), static_cast<int>(_right));
	int max = FMath::Max(static_cast<int>(_left), static_cast<int>(_right));

	if (m_collisionCheck[min] & (1 << max))
		return true;

	return false;
}
