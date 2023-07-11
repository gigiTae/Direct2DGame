#pragma once

#include "Broadphase.h"
#include "AABB.h"
#include "Collider.h"
struct Node;

/// <summary>
/// 충돌 체크 알고리즘 AABBTree
/// 각각의 콜라이더를 AABB사각형으로 확장하고
/// 확장한 사각형을 m_margin만큼 확장한후에 
/// 면적에따라서 Tree를 구성하고 정렬한다
/// 
/// </summary>
class AABBTree :
    public Broadphase
{
public:
    AABBTree(float _margin);
    ~AABBTree();

    void Add(Collider* _collider) override;
    void Remove(Collider* _collider) override;
    void Update() override;
    ColliderPairList& ComputePairs() override;
    void Pick(const Vector2& _point, ColliderVector& _colliderVector) override;
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
    const float m_margin;

    NodeVector m_invalidNodes;
};

struct Node
{
    Node() :parent(nullptr)
        , collider(nullptr)
        , children{ nullptr,nullptr } 
        , childrebCrossed(false)
        , aabb()
    {}
    
    bool IsLeaf()const
    {
        return children[0] == nullptr;
    }

    // 자식노드에 추가
    void SetBranch(Node* _n0, Node* _n1)
    {
        _n0->parent = this;
        _n1->parent = this;

        children[0] = _n0;
        children[1] = _n1;
    }

    // Leaf노드로 만든다
    void SetLeaf(Collider* _collider)
    {
        this->collider = _collider;
 
        children[0] = nullptr;
        children[1] = nullptr;
    }

    void UpdateAABB(float _margin)
    {
        if (IsLeaf())
        {
            // make fat AABB
            // 확장한 AABB생성
            const Vector2 marginVec(_margin, _margin);
            aabb.minPoint = collider->GetMinPoint() - marginVec;
            aabb.maxPoint = collider->GetMaxPoint() + marginVec;
        }
        else
        {
            // make union of child AABBs of child nodes;
            // 자식노드를 조합해서 AABB만들기
            aabb = children[0]->aabb.Union(children[1]->aabb);
        }
    }

    // 형제 반환
    Node* GetSibling() const
    {
        assert(parent);
        return this == parent->children[0] ? parent->children[1] : parent->children[0];
    }


    Node* parent;
    Node* children[2];

    bool childrebCrossed;
    AABB aabb;
    Collider* collider;
}; 