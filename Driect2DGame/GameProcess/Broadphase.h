#pragma once

class Collider;

typedef std::pair<Collider*, Collider*> ColliderPair;
typedef std::list<ColliderPair> ColliderPairList;

struct AABB;

/// <summary>
/// 광역 충돌체크 알고리즘 인터페이스이다 
/// 
/// </summary>
class Broadphase abstract
{
public:

	// add a new AABB to the broadphase
	// 새로운 AABB를 삽입
	virtual void Add(AABB* _aabb) = 0;
	
	// update broadphase to react to changes to AABB 
	// AABB의 변경사항에 반응하도록 broadphase을 업데이트
	virtual void Update() = 0;

	// returns a list of possible colliding colliders
	// 충돌 가능한 콜라이더 페어를 반환한다
	virtual const ColliderPairList& ComputePairs() = 0;

	// returns a collider that collides with a point
	// returns null if no such collider exists
	// 점과 충돌하는 충돌체를 반환한다.
	// 그러한 충돌체가 존재하지 않으면 null을 반환합니다.
	virtual Collider* Pick(const Vector2& _point) const = 0;

	// returns a list of colliders whose AABBs collide
	// with a query AABB
	// AABB가 충돌하는 충돌체 목록을 반환 합니다. 쿼리 AABB 사용
	typedef std::vector<Collider*> ColliderVector;
	virtual void Query(const AABB& _aabb, ColliderVector& _output) const = 0;

	

};
