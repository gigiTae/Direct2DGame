#pragma once

class GameObject;
class Transform;
/// <summary>
/// ������ �ٵ� ������Ʈ
/// �������� ������ ���� ó���� ��
/// ���� ������ ����� ���� ���� ������Ʈ
/// </summary>
class RigidBody
{
public:
	RigidBody(GameObject* _owner, float _mass, Vector2 _scale);
	~RigidBody();

	void IntegrateForces(float _fixedDeltaTime);
	void FinalUpdate(float _fixedDeltaTime);

	void AddForce(const Vector2& _force) { m_force += _force; }
	void AddToque(const float& _toque) { m_torque += _toque; }
	void ApplyImpulse(const Vector2& _impulse, const Vector2& _contactVector);

private: // ������� ����
	GameObject* m_owner;
	Transform* m_transform;

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

