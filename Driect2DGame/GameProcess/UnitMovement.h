#pragma once

#include "MonoBehaviour.h"

class Unit;
class GameObject;

/// <summary>
/// 유닛의 움직임을 담당하는 컴포넌트 
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
	Vector2 m_destination; // 최종목적지

};

