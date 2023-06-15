#include "GameProcessPCH.h"
#include "RigidBody.h"
#include "GameObject.h"

RigidBody::~RigidBody()
{
}

void RigidBody::FinalUpdate()
{
}

void RigidBody::Initalize(float _mass, GameObject* _owner)
{
	m_owner = _owner;
	assert(m_owner->GetTransform());

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
