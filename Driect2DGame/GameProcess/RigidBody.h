#pragma once

class GameObject;
class Transform;
/// <summary>
/// 리지드 바디 컴포넌트
/// 오브젝의 물리에 관한 처리를 함
/// 물리 엔진을 만들기 위한 기초 컴포넌트
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

private: // 멤버변수 공간
	GameObject* m_owner;
	Transform* m_transform;

	// 속도
	Vector2 m_velocity;
	// 각속도 
	float m_angularVelocity;
	// 힘
	Vector2 m_force;
	// 토크
	float m_torque;
	// 마찰력
	float m_friction;
	// 질량
	float m_mass, m_invMass;
	// 관성 모멘트
	float m_I, m_invI;
};

