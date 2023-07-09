#pragma once

class Unit;
class GameObject;
/// <summary>
/// ������ �������� ����ϴ� ������Ʈ�� �������̽�
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
	float m_moveSpeed; // �̵��ӵ�
	GameObject* m_gameoject;
	Unit* m_unitComponent;
};

