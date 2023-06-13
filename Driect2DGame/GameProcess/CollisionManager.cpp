
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
	// ��Ʈ �����ڸ� ���ؼ� �׷찣�� �浹������ �����Ѵ�.
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
		// �浹���� ���� ������ ���� ����
		m_prevCollisionInfo.insert(std::make_pair(ID.ID, false));

		// ������ ������ �ٽ� ã�Ƽ� iterator�� ������.
		iter = m_prevCollisionInfo.find(ID.ID);
	}

}

bool CollisionManager::IsCollision(BoxCollider* _leftBox, BoxCollider* _rightBox)
{
	// �ڽ�
	Vector2 leftPosition =_leftBox->GetPosition();
	Vector2 leftScale = _leftBox->GetScale();
	
	// �ڽ�
	Vector2 rightPosition = _rightBox->GetPosition();
	Vector2 rightScale = _rightBox->GetScale();

	// OBB �浹ó�� 
	if (_leftBox->IsRotatable() || _rightBox->IsRotatable())
	{
		// ȸ������
		float leftRotation = _leftBox->GetRotation();
		float rightRotation = _rightBox->GetRotation();

		Vector2 boxToBox = rightPosition - leftPosition;

		// ������ ���μ��� ���͸� ���Ѵ�.
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
	// AABB �浹
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
	// �ڽ� 
	Vector2 boxPosition = _leftBox->GetPosition();
	Vector2 boxHalfScale = _leftBox->GetScale() * 0.5f;
	
	// ��
	Vector2 circlePoisiton = _rightCircle->GetPosition();
	float radius = _rightCircle->GetRadius();

	// ȸ���� �簢���� ���� �浹 -> ������ ���� ������ �����
	if (_leftBox->IsRotatable())
	{
		float rotation = _leftBox->GetRotation();
		circlePoisiton = Vector2::RotateRadian(circlePoisiton, boxPosition, rotation);
	}

	float minBoxX = boxPosition.x - boxHalfScale.x;
	float maxBoxX = boxPosition.x + boxHalfScale.x;
	float minBoxY = boxPosition.y - boxHalfScale.y;
	float maxBoxY = boxPosition.y + boxHalfScale.y;

	// 1. ���� �簢���� ������ ��������ŭ Ȯ���ؼ� ���� �߽���ǥ�� ���ؼ� �Ǵ�
	if ((minBoxX - radius <= circlePoisiton.x && maxBoxX + radius >= circlePoisiton.x
		&& minBoxY <= circlePoisiton.y && maxBoxY >= circlePoisiton.y) ||
		(minBoxX <= circlePoisiton.x && maxBoxX >= circlePoisiton.x
			&& maxBoxY + radius >= circlePoisiton.y && minBoxY - radius <= circlePoisiton.y))
	{
		return true;
	}
	
	// 2. ���� ����� �簢���� ������ ��ǥ�� ����ؼ� ������ �Ÿ��� ��� 
	Vector2 boxVertex{};
	boxVertex.x = (boxPosition.x < circlePoisiton.x) ? maxBoxX : minBoxX;
	boxVertex.y = (boxPosition.y < circlePoisiton.y) ? maxBoxY : minBoxY;

	float distanceSquared = (boxVertex - circlePoisiton).SizeSquared();
	if (distanceSquared <= radius*radius)
	{
		return true;
	}

	// �浹���� ����
	return false;
}

bool CollisionManager::IsCollision(CircleCollider* _leftCircle, CircleCollider* _rightCircle)
{
	// ���� ���� �浹
	
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
	// �浹 ����
	Collision collision{};
	// ���� ������ �浹 ����
	bool isCollision = _isCollision;
	// ���� ������ �浹 ����
	bool isPrevCollison = iter->second;

	GameObject* leftObject = _leftCollider->GetOwner();
	assert(leftObject);
	GameObject* rightObject = _rightCollider->GetOwner();
	assert(rightObject);

	// ����ؼ� �浹���� ����
	if (_isCollision && isPrevCollison)
	{
		if (leftObject->IsAlive() && rightObject->IsAlive())
		{
			_leftCollider->OnCollisionStay(collision, m_inputManager);
			_rightCollider->OnCollisionStay(collision, m_inputManager);
		}
		else // �����ϳ��� ���������̶�� ����ó��
		{ 
			_leftCollider->OnCollisionExit(collision, m_inputManager);
			_rightCollider->OnCollisionExit(collision, m_inputManager);
			iter->second = false;
		}
	}
	else if(_isCollision && !isPrevCollison)
	{
		// �����ϳ��� ���� �����̶�� �浹���� ���������� ���
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
	// ���Ŵ����� ���ؼ� ������� �޾ƿ´�.
	Scene* currentScene = m_sceneManager->GetCurrentScene();
	assert(currentScene);

	// ���� ������ �����ϰ��ִ� �׷��� �޾ƿ´�.
	const vector<GameObject*>& leftGroup = currentScene->GetGroupObject(_left);
	const vector<GameObject*>& rightGroup = currentScene->GetGroupObject(_right);

	// ���� �迭�� ������ �迭�� ������Ʈ���� ��ȸ�ϸ鼭 �浹ó���� �Ѵ�.
	for (size_t leftIndex = 0; leftIndex < leftGroup.size(); ++leftIndex)
	{
		BoxCollider* leftBoxCollider = leftGroup[leftIndex]->GetBoxCollider();
		CircleCollider* leftCircleCollidr = leftGroup[leftIndex]->GetCircleCollider();

		// ���� ������Ʈ�� �ݶ��̴��� ��� ���� �ʴ°��
		if (!leftBoxCollider && !leftCircleCollidr)
		{
			continue;
		}

		for (size_t rightIndex = 0; rightIndex < rightGroup.size(); ++rightIndex)
		{
			BoxCollider* rightBoxCollider = rightGroup[rightIndex]->GetBoxCollider();
			CircleCollider* rightCircleCollidr = rightGroup[rightIndex]->GetCircleCollider();

			// ������ ������Ʈ�� �ݶ��̴��� �������� �ʴ� ����̰ų� ���� ������Ʈ�� ���
			if ( (!rightBoxCollider && !rightCircleCollidr) && leftGroup[leftIndex] == rightGroup[rightIndex])
			{
				continue;
			}
			 
			// ���� ��ȸ�ϴ� ���ͷ����� 
			map<unsigned long long, bool > ::iterator iter;
			// �浹���θ� �Ǵ�
			bool isCollision = false;

			// �ݶ��̴��� ������ ���� �浹ó���� �ٸ��� �ϴ� �б���
			// 1. AABB or OBB
			if (leftBoxCollider && rightBoxCollider)
			{
				CheckID(leftBoxCollider, rightBoxCollider, iter);
				isCollision =IsCollision(leftBoxCollider, rightBoxCollider);
				OnCollisionProcess(isCollision, iter, leftBoxCollider, rightBoxCollider);
			}
			// �ڽ� �� �� 
			if (leftBoxCollider && rightCircleCollidr)
			{
				CheckID(leftBoxCollider, rightCircleCollidr, iter);
				isCollision = IsCollision(leftBoxCollider, rightCircleCollidr);
				OnCollisionProcess(isCollision, iter, leftBoxCollider, rightCircleCollidr);
			}
			// ���� �ڽ�
			if (leftCircleCollidr && rightBoxCollider)
			{
				CheckID(leftCircleCollidr, rightBoxCollider, iter);
				isCollision = IsCollision(rightBoxCollider, leftCircleCollidr);
				OnCollisionProcess(isCollision, iter, leftCircleCollidr, rightBoxCollider);
			}
			// ���� ���� �浹
			if (leftCircleCollidr && rightCircleCollidr)
			{
				CheckID(leftCircleCollidr, rightCircleCollidr, iter);
				isCollision = IsCollision(leftCircleCollidr, rightCircleCollidr);
				OnCollisionProcess(isCollision, iter, leftCircleCollidr, rightCircleCollidr);
			}

		}
	}
}
