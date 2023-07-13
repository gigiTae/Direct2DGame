#pragma once

#include "MonoBehaviour.h"

class Unit;
class GameObject;

/// <summary>
/// ������ �������� ����ϴ� ������Ʈ 
/// 
/// </summary>
class UnitMovement : public MonoBehaviour 
{
public:
	UnitMovement(const string& _name);
	~UnitMovement();

	void Start() override;
	void SetDestination(Vector2 _dest);
	virtual bool Move(float _deltaTime) =0;

public:
	Unit* m_unit;
	Vector2 m_destination; // ����������

};

