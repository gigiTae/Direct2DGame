
#include"GameProcessPCH.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Scene.h"

CollisionManager::CollisionManager()
	:m_inputManager(nullptr)
	,m_sceneManager(nullptr)
	,m_collisionCheck{}
	,m_prevCollisionInfo{}
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Initalize(InputManager* _inputManager, SceneManager* _sceneManager)
{
	m_inputManager = _inputManager;
	m_sceneManager = _sceneManager;
}

void CollisionManager::Update()
{	
	for (int i = 0; i < static_cast<int>(OBJECT_TYPE::END); ++i)
	{
		for (int j = i; j < static_cast<int>(OBJECT_TYPE::END); ++j)
		{
			if (m_collisionCheck[i] & (i << j))
			{
				CollisionGroupUpdate(static_cast<OBJECT_TYPE>(i), static_cast<OBJECT_TYPE>(j));
			}
		}
	}
}

void CollisionManager::Finalize()
{
}

void CollisionManager::CheckCollisionObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right)
{
	// 비트 연산자를 통해서 그룹간의 충돌정보를 관리한다.
	m_collisionCheck[static_cast<int>(_left)] |= (1 << static_cast<int>(_right));
	m_collisionCheck[static_cast<int>(_right)] |= (1 << static_cast<int>(_left));
}

void CollisionManager::CheckID(const Collider* _left, const Collider* _right, map<unsigned long long, bool>::iterator& iter)
{
	unsigned int leftID = _left->GetID();
	unsigned int rightID = _right->GetID();

	CollisionID ID = CombineID(leftID, rightID);
	iter = m_prevCollisionInfo.find(ID.ID); 

	if (iter == m_prevCollisionInfo.end())
	{
		// 충돌하지 않은 것으로 정보 삽입
		m_prevCollisionInfo.insert(std::make_pair(ID.ID, false));

		// 삽입한 정보를 다시 찾아서 iterator에 가진다.
		iter = m_prevCollisionInfo.find(ID.ID);
	}

}

bool CollisionManager::IsCollision(BoxCollider* _leftBox, BoxCollider* _rightBox)
{
	// 박스
	Vector2 leftPosition =_leftBox->GetPosition();
	Vector2 leftScale = _leftBox->GetScale();
	
	// 박스
	Vector2 rightPosition = _rightBox->GetPosition();
	Vector2 rightScale = _rightBox->GetScale();

	// OBB 충돌처리 
	if (_leftBox->IsRotatable() || _rightBox->IsRotatable())
	{
		// 회전각도
		float leftRotation = _leftBox->GetRotation();
		float rightRotation = _rightBox->GetRotation();

		Vector2 boxToBox = rightPosition - leftPosition;

		// 각각의 가로세로 벡터를 구한다.
		Vector2 leftWidth = Vector2::RotateRadian(Vector2(leftScale.x *0.5f, 0.f), Vector2::Zero, leftRotation);
		Vector2 leftHeight = Vector2::RotateRadian(Vector2(0.f, leftScale.y *0.5f), Vector2::Zero, leftRotation);
		Vector2 rightWidth = Vector2::RotateRadian(Vector2(rightScale.x *0.5f, 0.f), Vector2::Zero, rightRotation);
		Vector2 rightHeight = Vector2::RotateRadian(Vector2(0.f, rightScale.y *0.5f), Vector2::Zero, rightRotation);

		vector<Vector2> basis{ leftWidth,leftHeight,rightWidth,rightHeight };

		for (int i = 0; i < 4; ++i)
		{
			float sum = 0.f;
			Vector2 normal = basis[i].GetNormalize();
			for (int j = 0; j < 4; ++j)
			{
				sum += abs(normal.Dot(basis[j]));
			}
			
			float distance = abs(boxToBox.Dot(normal));
			if (distance >= sum)
			{
				return false;
			}
		}
		return true;
	}
	// AABB 충돌
	else
	{
		Vector2 leftMin = leftPosition - leftScale * 0.5f;
		Vector2 leftMax = leftPosition + leftScale * 0.5f;
		Vector2 rightMin = rightPosition - rightScale * 0.5f;
		Vector2 rightMax = rightPosition + rightScale * 0.5f;

		if (leftMin.x <= rightMax.x && leftMax.x >= rightMin.x
			&& leftMin.y <= rightMax.y && leftMax.y >= rightMin.y)
			return true;
	}
	return false;
}

bool CollisionManager::IsCollision(BoxCollider* _leftBox, CircleCollider* _rightCircle)
{  
	// 박스 
	Vector2 boxPosition = _leftBox->GetPosition();
	Vector2 boxHalfScale = _leftBox->GetScale() * 0.5f;
	
	// 원
	Vector2 circlePoisiton = _rightCircle->GetPosition();
	float radius = _rightCircle->GetRadius();

	// 회전된 사각형과 원의 충돌 -> 역으로 원을 돌려서 계산함
	if (_leftBox->IsRotatable())
	{
		float rotation = _leftBox->GetRotation();
		circlePoisiton = Vector2::RotateRadian(circlePoisiton, boxPosition, rotation);
	}

	float minBoxX = boxPosition.x - boxHalfScale.x;
	float maxBoxX = boxPosition.x + boxHalfScale.x;
	float minBoxY = boxPosition.y - boxHalfScale.y;
	float maxBoxY = boxPosition.y + boxHalfScale.y;

	// 1. 먼저 사각형의 변들을 반지름만큼 확장해서 원의 중심좌표와 비교해서 판단
	if ((minBoxX - radius <= circlePoisiton.x && maxBoxX + radius >= circlePoisiton.x
		&& minBoxY <= circlePoisiton.y && maxBoxY >= circlePoisiton.y) ||
		(minBoxX <= circlePoisiton.x && maxBoxX >= circlePoisiton.x
			&& maxBoxY + radius >= circlePoisiton.y && minBoxY - radius <= circlePoisiton.y))
	{
		return true;
	}
	
	// 2. 가장 가까운 사각형의 꼭지점 좌표를 계산해서 원과의 거리를 계산 
	Vector2 boxVertex{};
	boxVertex.x = (boxPosition.x < circlePoisiton.x) ? maxBoxX : minBoxX;
	boxVertex.y = (boxPosition.y < circlePoisiton.y) ? maxBoxY : minBoxY;

	float distanceSquared = (boxVertex - circlePoisiton).SizeSquared();
	if (distanceSquared <= radius*radius)
	{
		return true;
	}

	// 충돌하지 않음
	return false;
}

bool CollisionManager::IsCollision(CircleCollider* _leftCircle, CircleCollider* _rightCircle)
{
	// 원과 원의 충돌
	
	Vector2 leftPosition = _leftCircle->GetPosition();
	float leftRadius = _leftCircle->GetRadius();

	Vector2 rightPosition = _rightCircle->GetPosition();
	float rightRaius = _rightCircle->GetRadius();

	float distance = (leftPosition - rightPosition).Size();
	
	if (distance <= rightRaius + leftRadius)
	{
		return true;
	}

	return false;
}

void CollisionManager::OnCollisionProcess(bool _isCollision, map<unsigned long long, bool>::iterator& iter, Collider* _leftCollider, Collider* _rightCollider)
{
	// 충돌 정보
	Collision collision{};
	// 현재 프레임 충돌 여부
	bool isCollision = _isCollision;
	// 이전 프레임 충돌 여부
	bool isPrevCollison = iter->second;

	GameObject* leftObject = _leftCollider->GetOwner();
	assert(leftObject);
	GameObject* rightObject = _rightCollider->GetOwner();
	assert(rightObject);

	// 계속해서 충돌중인 상태
	if (_isCollision && isPrevCollison)
	{
		if (leftObject->IsAlive() && rightObject->IsAlive())
		{
			_leftCollider->OnCollisionStay(collision, m_inputManager);
			_rightCollider->OnCollisionStay(collision, m_inputManager);
		}
		else // 둘중하나가 삭제예정이라면 예외처리
		{ 
			_leftCollider->OnCollisionExit(collision, m_inputManager);
			_rightCollider->OnCollisionExit(collision, m_inputManager);
			iter->second = false;
		}
	}
	else if(_isCollision && !isPrevCollison)
	{
		// 둘중하나가 삭제 예정이라면 충돌하지 않은것으로 취급
		if (leftObject->IsAlive() && rightObject->IsAlive())
		{
			_leftCollider->OnCollisionEnter(collision, m_inputManager);
			_rightCollider->OnCollisionEnter(collision, m_inputManager);
			iter->second = true;
		}
	}
	else if (!_isCollision && isPrevCollison)
	{
		_leftCollider->OnCollisionExit(collision, m_inputManager);
		_rightCollider->OnCollisionExit(collision, m_inputManager);
		iter->second = false;
	}

}

const CollisionID CollisionManager::CombineID(unsigned int _left, unsigned int _right)
{
	CollisionID collisionID = {};
	collisionID.leftID = _left;
	collisionID.rightID = _right;

	return collisionID;
}

void CollisionManager::CollisionGroupUpdate(OBJECT_TYPE _left, OBJECT_TYPE _right)
{
	// 씬매니져를 통해서 현재씬을 받아온다.
	Scene* currentScene = m_sceneManager->GetCurrentScene();
	assert(currentScene);

	// 현재 씬에서 저장하고있는 그룹을 받아온다.
	const vector<GameObject*>& leftGroup = currentScene->GetGroupObject(_left);
	const vector<GameObject*>& rightGroup = currentScene->GetGroupObject(_right);

	// 왼쪽 배열과 오른쪽 배열의 오브젝트들을 순회하면서 충돌처리를 한다.
	for (size_t leftIndex = 0; leftIndex < leftGroup.size(); ++leftIndex)
	{
		BoxCollider* leftBoxCollider = leftGroup[leftIndex]->GetBoxCollider();
		CircleCollider* leftCircleCollidr = leftGroup[leftIndex]->GetCircleCollider();

		// 왼쪽 오브젝트가 콜라이더를 들고 있지 않는경우
		if (!leftBoxCollider && !leftCircleCollidr)
		{
			continue;
		}

		for (size_t rightIndex = 0; rightIndex < rightGroup.size(); ++rightIndex)
		{
			BoxCollider* rightBoxCollider = rightGroup[rightIndex]->GetBoxCollider();
			CircleCollider* rightCircleCollidr = rightGroup[rightIndex]->GetCircleCollider();

			// 오른쪽 오브젝트가 콜라이더를 소유하지 않는 경우이거나 같은 오브젝트인 경우
			if ( (!rightBoxCollider && !rightCircleCollidr) && leftGroup[leftIndex] == rightGroup[rightIndex])
			{
				continue;
			}
			 
			// 맵을 순회하는 이터레이터 
			map<unsigned long long, bool > ::iterator iter;
			// 충돌여부를 판단
			bool isCollision = false;

			// 콜라이더의 종류에 따라서 충돌처리를 다르게 하는 분기점
			// 1. AABB or OBB
			if (leftBoxCollider && rightBoxCollider)
			{
				CheckID(leftBoxCollider, rightBoxCollider, iter);
				isCollision =IsCollision(leftBoxCollider, rightBoxCollider);
				OnCollisionProcess(isCollision, iter, leftBoxCollider, rightBoxCollider);
			}
			// 박스 와 원 
			if (leftBoxCollider && rightCircleCollidr)
			{
				CheckID(leftBoxCollider, rightCircleCollidr, iter);
				isCollision = IsCollision(leftBoxCollider, rightCircleCollidr);
				OnCollisionProcess(isCollision, iter, leftBoxCollider, rightCircleCollidr);
			}
			// 원과 박스
			if (leftCircleCollidr && rightBoxCollider)
			{
				CheckID(leftCircleCollidr, rightBoxCollider, iter);
				isCollision = IsCollision(rightBoxCollider, leftCircleCollidr);
				OnCollisionProcess(isCollision, iter, leftCircleCollidr, rightBoxCollider);
			}
			// 원과 원의 충돌
			if (leftCircleCollidr && rightCircleCollidr)
			{
				CheckID(leftCircleCollidr, rightCircleCollidr, iter);
				isCollision = IsCollision(leftCircleCollidr, rightCircleCollidr);
				OnCollisionProcess(isCollision, iter, leftCircleCollidr, rightCircleCollidr);
			}

		}
	}
}
