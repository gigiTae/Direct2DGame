
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
	// OBB �浹ó�� 
	if (_leftBox->IsRotatable() || _rightBox->IsRotatable())
	{

	}
	else // AABB �浹
	{

	}
	return false;
}

bool CollisionManager::IsCollision(BoxCollider* _leftBox, CircleCollider* _rightCircle)
{

	// ȸ���� �簢���� ���� �浹
	if (_leftBox->IsRotatable())
	{

	}
	else // �簢���� ���� �浹
	{
	
	}

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
		if (!leftBoxCollider && leftCircleCollidr)
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
