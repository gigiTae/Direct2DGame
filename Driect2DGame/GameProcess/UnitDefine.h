#pragma once

/// Unit에 필요한 정의을 나열한 헤더이다


enum class UNIT_STATE
{
	HOLD, // 정지상태로 공격범위내에 적을 식별하면 HOLD_ATTACK 상태가 된다.
	HOLD_ATTACK, // 정지 공격상태로 적이 공격범위 밖으로가면 공격을 중단하고 새로운 타겟을 찾는다.
	TRACK, // 추적상태 공격범위 밖으로 적이 이동해서 추적하는 상태이다.
	ATTACK, // 공격범위내에 적이 존재해서 공격하는 상태 
	MOVE, // 이동상태 
	DEAD, // 죽은 상태 
};

enum class ATTACK_TYPE
{
	NONE,  // 공격하지 않음
	KNIFE, // 칼
	MAGIC, // 마법
	GUN, // 총
};

// 가장 기본적인 유닛의 정보
struct UnitInfomaiton
{
	UNIT_STATE state; // 유닛 상태
	float hp; // 체력
	float moveSpeed; // 이동속도

	/// 전투관련
	ATTACK_TYPE attackType; // 공격타입

	float attackPower; // 공격력
	float attackRange; // 공격범위
	float attackSpeed; // 공격속도
};