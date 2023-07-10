#include "GameProcessPCH.h"
#include "AABB.h"

AABB::AABB()
{

}

AABB::AABB(const Vector2& _minPoint, const Vector2& _maxPoint)
{

}


AABB AABB::Union(const AABB& _other) const
{
	AABB tmp{};

	tmp.minPoint.x = FMath::Min(minPoint.x, _other.minPoint.x);
	tmp.minPoint.y = FMath::Min(minPoint.y, _other.minPoint.y);
	tmp.maxPoint.x = FMath::Max(maxPoint.x, _other.maxPoint.x);
	tmp.maxPoint.y = FMath::Max(maxPoint.y, _other.maxPoint.y);

	return tmp;
}

float AABB::GetArea() const
{
	return ((maxPoint.x - minPoint.x) * (maxPoint.y - minPoint.y));
}
