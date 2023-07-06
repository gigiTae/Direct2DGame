#pragma once

#include "Component.h"

class GameObject;
class Transform;
/// <summary>
/// 리지드 바디 컴포넌트
/// 오브젝의 물리에 관한 처리를 함
/// 물리 엔진을 만들기 위한 기초 컴포넌트
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

private: // 멤버변수 공간
	Transform* m_transform;
	// 속도
	Vector2 m_velocity;
	// 각속도 
	float m_angularVelocity;
	// 힘
	Vector2 m_force;
	// 토크
	float m_torque;
	// 질량
	float m_mass, m_invMass;
	// 관성 모멘트
	float m_I, m_invI;
};

