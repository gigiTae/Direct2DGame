#pragma once

/// Unit�� �ʿ��� ������ ������ ����̴�


enum class UNIT_STATE
{
	HOLD, // �������·� ���ݹ������� ���� �ĺ��ϸ� HOLD_ATTACK ���°� �ȴ�.
	HOLD_ATTACK, // ���� ���ݻ��·� ���� ���ݹ��� �����ΰ��� ������ �ߴ��ϰ� ���ο� Ÿ���� ã�´�.
	TRACK, // �������� ���ݹ��� ������ ���� �̵��ؼ� �����ϴ� �����̴�.
	ATTACK, // ���ݹ������� ���� �����ؼ� �����ϴ� ���� 
	MOVE, // �̵����� 
	DEAD, // ���� ���� 
};

enum class ATTACK_TYPE
{
	NONE,  // �������� ����
	KNIFE, // Į
	MAGIC, // ����
	GUN, // ��
};


enum class LAND_TYPE
{
	GROUND, // ����
	SKY, // �ϴ�
	WATER, // �Ƹ� ��������� ���� ���ҵ�
};

enum class TEAM
{
	ALLY, // �Ʊ� 
	ENEMY, // ����
};

// ���� �⺻���� ������ ����
struct UnitInfomaiton
{
	TEAM team; //
	LAND_TYPE landType; // ������ ��� ���ϴ���
	UNIT_STATE state; // ���� ����
	float currentHP; // ���� ü��
	float maxHP; // �ִ� ü��
	float moveSpeed; // �̵��ӵ�

	/// ��������
	ATTACK_TYPE attackType; // ����Ÿ��

	float attackPower; // ���ݷ�
	float attackRange; // ���ݹ���
	float attackSpeed; // ���ݼӵ�
};