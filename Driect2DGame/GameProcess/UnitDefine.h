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

// ���� �⺻���� ������ ����
struct UnitInfomaiton
{
	UNIT_STATE state; // ���� ����
	float hp; // ü��
	float moveSpeed; // �̵��ӵ�

	/// ��������
	ATTACK_TYPE attackType; // ����Ÿ��

	float attackPower; // ���ݷ�
	float attackRange; // ���ݹ���
	float attackSpeed; // ���ݼӵ�
};