#pragma once

#include "Broadphase.h"
#include "AABB.h"

struct Node;

/// <summary>
/// �浹 üũ �˰��� AABBTree
/// 
/// </summary>
class AABBTree :
    public Broadphase
{
public:
    AABBTree();
    ~AABBTree();

    void Add(AABB* _aabb) override;
    virtual void ReMove(AABB* _aabb);
    void Update() override;
    ColliderPairList& ComputePairs() override;
    Collider* Pick(const Vector2& _point)const override;
    void Query(const AABB& _aabb, ColliderVector& _output) const override;

private:
    typedef std::vector<Node*> NodeVector;

    void UpdateNodeHelper(Node* _node, NodeVector& _invalidNodes);
    void InsertNode(Node* _node, Node** _parent);
    void RemoveNode(Node* _node);
    void ComputePairsHelper(Node* _n0, Node* _n1);
    void ClearChildrenCrossFlagHelper(Node* _node);
    void CrossChildren(Node* _node);

    Node* m_root;
    ColliderPairList m_pairs;
    float m_margin;
    NodeVector m_invalidNodes;

};

struct Node
{
    Node();
    
    bool IsLeaf()const
    {
        return children[0] == nullptr;
    }

    // �ڽĳ�忡 �߰�
    void SetBranch(Node* _n0, Node* _n1)
    {
        _n0->parent = this;
        _n1->parent = this;

        children[0] = _n0;
        children[1] = _n1;
    }

    // Leaf���� �����
    void SetLeaf(AABB* _data)
    {
        this->data = data;
 
        children[0] = nullptr;
        children[1] = nullptr;
    }

    void UpdateAABB(float _margin)
    {
        if (IsLeaf())
        {
            // make fat AABB
            // Ȯ���� AABB����
            const Vector2 marginVec(_margin, _margin);
            aabb.minPoint = data->minPoint - marginVec;
            aabb.maxPoint = data->maxPoint + marginVec;
        }
        else
        {
            // make union of child AABBs of child nodes;
            // �ڽĳ�带 �����ؼ� AABB�����
            aabb = children[0]->aabb.Union(children[1]->aabb);
        }
    }

    // ���� ��ȯ
    Node* GetSibling() const
    {
        return this == parent->children[0] ? parent->children[1] : parent->children[0];
    }


    Node* parent;
    Node* children[2];

    bool childrebCrossed;
    AABB aabb;
    AABB* data;
}; 