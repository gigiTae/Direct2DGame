#include "GameProcessPCH.h"
#include "RigidBody.h"
#include "Transform.h"
#include "GameObject.h"
#include "GameWorld.h"

RigidBody::~RigidBody()
{
}

void RigidBody::IntegrateForces(float _fixedDeltaTime)
{
	if (m_invMass == 0.f)
		return;

	// 힘을 가지고 속도를 갱신한다.
	m_velocity += (m_force * m_invMass + GameWorld::gravity) * _fixedDeltaTime;
	m_angularVelocity += m_torque * m_invI * _fixedDeltaTime;

	m_velocity *= std::exp(-GameWorld::linearDamping * _fixedDeltaTime);
	m_angularVelocity *= std::exp(-GameWorld::angularDamping * _fixedDeltaTime);
}

void RigidBody::FinalUpdate(float _deltaTime)
{
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

void RigidBody::Initalize(float _mass, GameObject* _owner)
{
	m_owner = _owner;
	assert(m_owner);
	m_transform = _owner->GetTransform();
	assert(m_transform);
	
	m_velocity = Vector2::Zero;
	m_angularVelocity = 0.f;
	m_force = Vector2::Zero;
	m_torque = 0.f;
	m_friction = 0.2f;

	m_mass = _mass;
	if (m_mass < FLT_MAX)
	{
		m_invMass = 1.0f / m_mass;
		//m_I = m_mass * (width.x * width.x + width.y * width.y) / 12.0f;
		m_invI = 1.0f / m_I;
	}
	else
	{
		m_invMass = 0.0f;
		m_I = FLT_MAX;
		m_invI = 0.0f;
	}
}
void RigidBody::ApplyImpulse(const Vector2& _impulse, const Vector2& _contactVector)
{
	m_velocity += _impulse * m_invMass;
	m_angularVelocity += _contactVector.Cross(_impulse) * m_invI;
}
