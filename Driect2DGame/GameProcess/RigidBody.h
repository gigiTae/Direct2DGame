#pragma once

class GameObject;
/// <summary>
/// ������ �ٵ� ������Ʈ
/// �������� ������ ���� ó���� ��
/// ���� ������ ����� ���� ���� ������Ʈ
/// </summary>
class RigidBody
{
public:
	RigidBody() = default;
	~RigidBody();

	void FinalUpdate();

	void Initalize(float _mass, GameObject* _owner);

private: // ������� ����
	GameObject* m_owner;

	// �ӵ�
	Vector2 m_velocity;
	// ���ӵ� 
	float m_angularVelocity;
	// ��
	Vector2 m_force;
	// ��ũ
	float m_torque;
	// ������
	float m_friction;
	// ����
	float m_mass, m_invMass;
	// ���� ���Ʈ
	float m_I, m_invI;
};

