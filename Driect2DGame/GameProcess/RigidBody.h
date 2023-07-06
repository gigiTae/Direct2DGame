#pragma once

#include "Component.h"

class GameObject;
class Transform;
/// <summary>
/// ������ �ٵ� ������Ʈ
/// �������� ������ ���� ó���� ��
/// ���� ������ ����� ���� ���� ������Ʈ
/// </summary>
class RigidBody : public Component
{
public:
	RigidBody();
	~RigidBody();

	void LateUpdate(float _deltaTime, const InputManager* _inputManager) override;
	void IntegrateForces(float _fixedDeltaTime);

	void AddForce(const Vector2& _force) { m_force += _force; }
	void AddToque(const float& _toque) { m_torque += _toque; }
	void ApplyImpulse(const Vector2& _impulse, const Vector2& _contactVector);

	void SetMass(float _mass);

	Vector2 GetVelocity() { return m_velocity; }

private: // ������� ����
	Transform* m_transform;
	// �ӵ�
	Vector2 m_velocity;
	// ���ӵ� 
	float m_angularVelocity;
	// ��
	Vector2 m_force;
	// ��ũ
	float m_torque;
	// ����
	float m_mass, m_invMass;
	// ���� ���Ʈ
	float m_I, m_invI;
};

