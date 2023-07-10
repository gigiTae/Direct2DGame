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
	/// ���ֿ��� �����̶�� ����� ������ �����ϸ� true�� ��ȯ�Ѵ�.
	virtual bool Move(float _deltaTime) abstract; 
	void Initalize(GameObject* _object, Unit* _unitComponent, float _movespeed);

	void SetDestination(const Vector2& _destination) { m_destination = _destination; }


protected:
	float m_moveSpeed; // �̵��ӵ�
	GameObject* m_gameoject;
	Unit* m_unitComponent;

	Vector2 m_destination; // ������ ���� ������
};

