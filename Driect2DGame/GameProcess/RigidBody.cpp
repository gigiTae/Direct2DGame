#include "GameProcessPCH.h"
#include "RigidBody.h"
#include "Transform.h"
#include "GameObject.h"
#include "GameWorld.h"

RigidBody::RigidBody()
	:m_angularVelocity(0.f)
	, m_torque(0.f)
	, m_force(Vector2::Zero)
	, m_velocity(Vector2::Zero)
	, m_mass(1.f)
	, m_invMass(1.f)
	, m_I(1.f)
	, m_invI(1.f)
	, m_transform(nullptr)
{}

RigidBody::~RigidBody()
{}

void RigidBody::SetMass(float _mass)
{
	m_mass = _mass;
	if (m_mass < FLT_MAX)
	{
		m_invMass = 1.0f / m_mass;
		m_I = m_mass;// *_scale.LengthSquared() / 12.0f;
		m_invI = 1.0f / m_I;
	}
	else
	{
		m_invMass = 0.0f;
		m_I = FLT_MAX;
		m_invI = 0.0f;
	}
}

void RigidBody::IntegrateForces(float _fixedDeltaTime)
{
	if (m_invMass == 0.f)
		return;

	// 힘을 가지고 속도를 갱신한다.
	m_velocity += (m_force * m_invMass + GameWorld::GRAVITY) * _fixedDeltaTime;
	m_angularVelocity += m_torque * m_invI * _fixedDeltaTime;

	m_velocity *= std::exp(-GameWorld::linearDamping * _fixedDeltaTime);
	m_angularVelocity *= std::exp(-GameWorld::angularDamping * _fixedDeltaTime);
}

void RigidBody::Update(float _deltaTime)
{
	if (m_transform == nullptr)
	{
		m_transform = GetComponent<Transform>();
	}

	// 현재의 속도를 가지고 오브젝트의 위치를 갱신한다.
	if (m_invMass == 0.f)
		return;
	Vector2 position = m_velocity * _deltaTime;
	m_transform->AddPosition(position);

	float rotation = m_angularVelocity * _deltaTime;
	m_transform->AddRotation(rotation);

	// 힘 초기화
	m_force = Vector2::Zero;
	m_torque = 0.f;
}

void RigidBody::ApplyImpulse(const Vector2& _impulse, const Vector2& _contactVector)
{
	m_velocity += _impulse * m_invMass;
	m_angularVelocity += _contactVector.Cross(_impulse) * m_invI;
}
