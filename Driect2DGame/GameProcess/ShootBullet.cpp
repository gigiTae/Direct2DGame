#include "GameProcessPCH.h"
#include "ShootBullet.h"
#include "Transform.h"
#include "GameObject.h"

ShootBullet::ShootBullet()
	:MonoBehaviour(typeid(this).name())
	,m_shootSpeed(0.f)
{

}

ShootBullet::~ShootBullet()
{

}

void ShootBullet::Update(float _deltaTime)
{
	Transform* transform = GetComponent<Transform>();

	Vector2 distance = m_direct * m_shootSpeed * _deltaTime;

	transform->AddPosition(distance);
}

void ShootBullet::Shoot(Vector2 _dircet, float _speed)
{
	m_direct = _dircet.GetNormalize();
	m_shootSpeed = _speed;
}
