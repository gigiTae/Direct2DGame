#include "GameProcessPCH.h"
#include "GameObject.h"
#include "AABBTree.h"
#include "CollisionManager.h"


AABBTree::AABBTree(float _margin, CollisionManager* _collisionManager)
	:m_margin(_margin)
	, m_root(nullptr)
	, m_invalidNodes{}
	, m_pairs{}
	,m_collisionManager(_collisionManager)
{

}

AABBTree::~AABBTree()
{
	// TODO : 메모리해제 

}

void AABBTree::Add(Collider* _aabb)
{
	if (m_root)
	{
		// not first node, insert node to tree
		Node* node = new Node();
		node->SetLeaf(_aabb);
		node->UpdateAABB(m_margin);
		InsertNode(node, &m_root);
	}
	else
	{
		// first node, make root
		m_root = new Node();
		m_root->SetLeaf(_aabb);
		m_root->UpdateAABB(m_margin);
	}
}

void AABBTree::Update()
{
	if (m_root)
	{
		if (m_root->IsLeaf())
			m_root->UpdateAABB(m_margin);
		else
		{
			// grab all invalid nodes
			// 모든 유효하지 않는 노드를 가져옵니다
			// 삭제된 오브젝트도 추가하자 
			m_invalidNodes.clear();
			UpdateNodeHelper(m_root, m_invalidNodes);

			// re-insert all invalid nodes
			// 유효하지 않는 모든 노드를 다시 삽입
			for (Node* node : m_invalidNodes)
			{
				// grab parent link
				// (pointer to the pointer that points to parent)
				// 부모 링크 잡기 (부모를 가리키는 포인터를 가리키는 포인터)
				Node* parent = node->parent;
				Node* siblibg = node->GetSibling();  
				Node** parentLink = parent->parent 
					? (parent == parent->parent->children[0]
						? &parent->parent->children[0]
						: &parent->parent->children[1])
					: &m_root;

				// replace parent with sibling
				siblibg->parent =
					parent->parent
					? parent->parent
					: nullptr; // root has null parent

				*parentLink = siblibg;
				delete parent;

				// re-insert node 
				// 트리에 다시확장 
				node->UpdateAABB(m_margin);
				InsertNode(node, &m_root);
			}
			m_invalidNodes.clear();
		}

	}
}

void AABBTree::UpdateNodeHelper(Node* _node, NodeVector& _invalidNodes)
{
	if (_node->IsLeaf())
	{
		// 삭제 예정인 오브젝트
		if (!_node->collider->GetGameObject()->IsAlive())
		{
			Remove(_node->collider);
		}
		else if (_node->aabb.Contains(_node->collider))
		{
			// check if fat AABB dosen't contain the collider's AABB anymore
			// 확장한 AABB박스에서 콜라이더가 벗어나면 invalidNodes에 데이터를 추가한다
			_invalidNodes.push_back(_node);
		}
 	}
	else
	{
		UpdateNodeHelper(_node->children[0], _invalidNodes);
		UpdateNodeHelper(_node->children[1], _invalidNodes);
	}
}


void AABBTree::InsertNode(Node* _node, Node** _parent)
{
	Node* p = *_parent;
	if (p->IsLeaf())
	{
		// parent is leaf, simply split
		// 부모가 리프노드, 간단히 분리
		Node* newParent = new Node();
		newParent->parent = p->parent;
		newParent->SetBranch(_node, p); 
		*_parent = newParent;
	}
	else
	{
		// parent is branch, compute volume differences
		// between pre-insert and post-insertㅌ
		// 부모가 브랜치이면, 삽입전과 후의 볼륨차이를 계산
		const AABB aabb0 = p->children[0]->aabb;
		const AABB aabb1 = p->children[1]->aabb;

		const float volumeDiff0 = aabb0.Union(_node->aabb).GetArea() - aabb0.GetArea();
		const float volumeDiff1 = aabb1.Union(_node->aabb).GetArea() - aabb1.GetArea();

		// insert to the child that gives less volume increase;
		// 볼륨 증가가 적은 자식노드에게 삽입한다.
		if (volumeDiff0 < volumeDiff1)
			InsertNode(_node, &p->children[0]);
		else
			InsertNode(_node, &p->children[1]);
	}

	// update parent AABB
	// (propagate back up the recursion stack)
	// 부모 AABB 업데이트 (재귀적인 호출)
	(*_parent)->UpdateAABB(m_margin);
}

void AABBTree::Remove(Collider* _collider)
{
	Node* node = _collider->GetNode();
	     
	// remove two-way link
	node->collider = nullptr;
	_collider->SetNode(node);

	RemoveNode(node);
}

void AABBTree::RemoveNode(Node* _node)
{
	// replace parent with sibling, remove parent node
	Node* parent = _node->parent;
	if (parent) // node is not root
	{
		Node* sibling = _node->GetSibling();
		if (parent->parent)// if there's a grandparent
		{
			// update links 
			sibling->parent = parent->parent;
			(parent == parent->parent->children[0]
				? parent->parent->children[0]
				: parent->parent->children[1]) = sibling;
		}
		else // no grandparent 
		{
			// make sibling root
			m_root = sibling;
			sibling->parent = nullptr;
		}
		delete _node;
		delete parent;
	}
	else // node is root
	{
		m_root = nullptr;
		delete _node;
	}

}

ColliderPairList& AABBTree::ComputePairs()
{
	m_pairs.clear();

	// early out
	if (!m_root || m_root->IsLeaf())
		return m_pairs;

	// clearNode::childrenCrossed flags
	ClearChildrenCrossFlagHelper(m_root);

	// base recursive call
	// 재귀적인 호출
	ComputePairsHelper(m_root->children[0], m_root->children[1]);

	return m_pairs;
 }


void AABBTree::ComputePairsHelper(Node* _n0, Node* _n1)
{
	if (_n0->IsLeaf())
	{
		// 2 leaves, check proxies instead of fat AABBs
		if (_n1->IsLeaf())
		{
			if (_n0->collider->Collides(_n1->collider))
			{
				m_pairs.push_back(std::make_pair(_n0->collider, _n1->collider));
			}
		}
		// 1 branch / 1 leaf, 2 cross checks
		else
		{
			CrossChildren(_n1);

			if (!_n0->aabb.IsCollision(_n1->aabb))
				return;

			ComputePairsHelper(_n0, _n1->children[0]);
			ComputePairsHelper(_n0, _n1->children[1]);
		}
	}
	else
	{
		// 1branch / l leaf, 2 cross checks
		if (_n1->IsLeaf())
		{
			if (!_n0->aabb.IsCollision(_n1->aabb))
				return;

			CrossChildren(_n0);
			ComputePairsHelper(_n0->children[0], _n1);
			ComputePairsHelper(_n0->children[1], _n1);
		}
		// 2 branches, 4 cross checks
		else
		{
			if (!_n0->aabb.IsCollision(_n1->aabb))
				return;

			CrossChildren(_n0);
			CrossChildren(_n1);
			ComputePairsHelper(_n0->children[0], _n1->children[0]);
			ComputePairsHelper(_n0->children[0], _n1->children[1]);
			ComputePairsHelper(_n0->children[1], _n1->children[0]);
			ComputePairsHelper(_n0->children[1], _n1->children[1]);
		} 
	} // end of if (_n0->IsLeaf())
	
}

void AABBTree::ClearChildrenCrossFlagHelper(Node* _node)
{
	_node->childrebCrossed = false;
	if (!_node->IsLeaf())
	{
		ClearChildrenCrossFlagHelper(_node->children[0]);
		ClearChildrenCrossFlagHelper(_node->children[1]);
	}
}

void AABBTree::CrossChildren(Node* _node)
{
	if (!_node->childrebCrossed)
	{
		ComputePairsHelper(_node->children[0], _node->children[1]);
		_node->childrebCrossed = true;
	}
}

void AABBTree::Pick(const Vector2& _point, ColliderVector& _colliderVector)
{
	std::queue<Node*> q;
	
	if (m_root)
		q.push(m_root);

	while (!q.empty())
	{
		Node& node = *q.front();
		q.pop();

		if (node.IsLeaf())
		{
			// 만약 충돌하는 경우
			if (node.collider->Collides(_point))
				_colliderVector.push_back(node.collider);
		}
		else
		{
			q.push(node.children[0]);
			q.push(node.children[1]);
		}
	}
}

void AABBTree::Query(const AABB& _aabb, ColliderVector& _output) const
{
	std::queue<Node*> q;
	
	if (m_root)
		q.push(m_root);

	while (!q.empty())
	{
		Node& node = *q.front();
		q.pop();

		if (node.IsLeaf())
		{
			// AABB 충돌
			Vector2 leftMax = node.collider->GetMaxPoint();
			Vector2 leftMin = node.collider->GetMinPoint();

			Vector2 rightMax = _aabb.maxPoint;
			Vector2 rightMin = _aabb.minPoint;

			if (leftMin.x <= rightMax.x && leftMax.x >= rightMin.x
				&& leftMin.y <= rightMax.y && leftMax.y >= rightMin.y)
			{
				_output.push_back(node.collider);
			}
		}
		else
		{
			q.push(node.children[0]);
			q.push(node.children[1]);
		}
	}
	
}

