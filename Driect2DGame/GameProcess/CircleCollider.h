#pragma once


/// <summary>
/// 원형 콜라이더 
/// 
/// </summary>
class CircleCollider
{
public:
	CircleCollider();
	~CircleCollider();

private:
	Vector2 m_position; 
	float m_radius;

};

