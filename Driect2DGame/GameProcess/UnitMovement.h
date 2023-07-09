#pragma once

class Unit;
class GameObject;
/// <summary>
/// 유닛의 움직임을 담당하는 컴포넌트의 인터페이스
/// 
/// </summary>
class UnitMovement abstract
{
public:
	UnitMovement();
	~UnitMovement();

public:
	virtual void Move(float _deltaTime) abstract; 
	void Initalize(GameObject* _object, Unit* _unitComponent, float _movespeed);

protected:
	float m_moveSpeed; // 이동속도
	GameObject* m_gameoject;
	Unit* m_unitComponent;
};

