#pragma once


struct AABB
{
	Vector2 minPoint;
	Vector2 maxPoint;

	AABB();
	AABB(const Vector2& _minPoint, const Vector2& _maxPoint);

	// 2���� AABB�� ����
	AABB Union(const AABB& _other)const;
	float GetArea()const;
};

