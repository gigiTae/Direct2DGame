#include "GameProcessPCH.h"
#include "AABBTree.h"

AABBTree::AABBTree()
{

}

AABBTree::~AABBTree()
{

}

void AABBTree::Add(AABB* _aabb)
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

void AABBTree::ReMove(AABB* _aabb)
{

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
			// ��� ��ȿ���� �ʴ� ��带 �����ɴϴ�
			m_invalidNodes.clear();
			UpdateNodeHelper(m_root, m_invalidNodes);

			// re-insert all invalid nodes
			// ��ȿ���� �ʴ� ��� ��带 �ٽ� ����
			for (Node* node : m_invalidNodes)
			{
				// grab parent link
				// (pointer to the pointer that points to parent)
				// �θ� ��ũ ��� (�θ� ����Ű�� �����͸� ����Ű�� ������)
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
				node->UpdateAABB(m_margin);
				InsertNode(node, &m_root);
			}
			m_invalidNodes.clear();
		}

	}
}

ColliderPairList& AABBTree::ComputePairs()
{

}

Collider* AABBTree::Pick(const Vector2& _point) const
{

}

void AABBTree::Query(const AABB& _aabb, ColliderVector& _output) const
{

}

void AABBTree::UpdateNodeHelper(Node* _node, NodeVector& _invalidNodes)
{

}

void AABBTree::InsertNode(Node* _node, Node** _parent)
{
	Node* p = *_parent;
	if (p->IsLeaf())
	{
		// parent is leaf, simply split
		// �θ� �������, ������ �и�
		Node* newParent = new Node();
		newParent->parent = p->parent;
		newParent->SetBranch(_node, p);
		*_parent = newParent;
	}
	else
	{
		// parent is branch, compute volume differences
		// between pre-insert and post-insert
		// �θ� �귣ġ�̸�, �������� ���� �������̸� ���
		const AABB aabb0 = p->children[0]->aabb;
		const AABB aabb1 = p->children[1]->aabb;

		const float volumeDiff0 = aabb0.Union(_node->aabb).GetArea() - aabb0.GetArea();
		const float volumeDiff1 = aabb1.Union(_node->aabb).GetArea() - aabb1.GetArea();

		// insert to the child that gives less volume increase;
		// ���� ������ ���� �ڽĳ�忡�� �����Ѵ�.
		if (volumeDiff0 < volumeDiff1)
			InsertNode(_node, &p->children[0]);
		else
			InsertNode(_node, &p->children[1]);
	}

	// update parent AABB
	// (propagate back up the recursion stack)
	// �θ� AABB ������Ʈ (������� ȣ��)
	(*_parent)->UpdateAABB(m_margin);
}

void AABBTree::RemoveNode(Node* _node)
{

}

void AABBTree::ComputePairsHelper(Node* _n0, Node* _n1)
{

}

void AABBTree::ClearChildrenCrossFlagHelper(Node* _node)
{

}

void AABBTree::CrossChildren(Node* _node)
{

}
