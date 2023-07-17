#include "GameProcessPCH.h"
#include "ShootBullet.h"
#include "Transform.h"
#include "TextureRenderer.h"
#include "GameObject.h"
#include "ManagerSet.h"
#include "Unit.h"
#include "Animator.h"
#include "SceneManager.h"

ShootBullet::ShootBullet()
	:MonoBehaviour(typeid(this).name())
	, m_shootSpeed(0.f)
	, m_prevDistance(0.f)
	,m_damage(0.f)
	,m_target(nullptr)
{

}

ShootBullet::~ShootBullet()
{

}

void ShootBullet::Update(float _deltaTime)
{
	// Ÿ���� �������� �Ѿ��� �ı��Ѵ�.
	if ( m_target == nullptr || !m_target->IsAlive())
	{
		m_target = nullptr;
	}

	Transform* transform = GetComponent<Transform>();
	
	// �Ѿ��� �̵��Ÿ���ŭ �̵��Ѵ�.
	Vector2 moveDistance = m_direct * _deltaTime * m_shootSpeed;
	transform->AddPosition(moveDistance);

	Vector2 position = transform->GetPosition();
	
	// �Ÿ��� ������ ���� �Ÿ����� ���������� �Ѿ��� �����ϰ� Ÿ�ٿ��� ������� �ش�.
	float currentDistance = (position - m_desitinaiton).LengthSquared();

	if (m_prevDistance <= currentDistance && GetGameObject()->GetObjectState() == OBJECT_STATE::ALIVE)
	{
		// �Ѿ� ����
		GetGameObject()->Destory();
		
		// ����� ����Ʈ
		GameObject* effect = new GameObject("effect", GetManagerSet(), OBJECT_TYPE::ATTACK_EFFECT);
		effect->CreateComponent<Transform>()->SetPosition(position);
		effect->CreateComponent<Animator>()->CreateAnimation(L"hitAnimation1", L"hitEffect1"
			, Vector2::Zero, Vector2(32.f, 32.f), Vector2(32.f, 0.f), 0.1f, 3);
		effect->GetComponent<Animator>()->Play(L"hitAnimation1", false);

		GetManagerSet()->GetSceneManager()->RegisterObject(effect);
		effect->Destory(0.3f);
	
		// ����� ����
		if (m_target != nullptr)
			m_target->GetComponent<Unit>()->TakeDamage(m_damage);
	}

	m_prevDistance = currentDistance;
}


void ShootBullet::Shoot(GameObject* _target, float _speed, float _damage)
{
	m_target = _target;
	m_shootSpeed = _speed;
	m_damage = _damage;

	// ���� �߻���ġ
	Transform* transform = GetComponent<Transform>();
	Vector2 position = transform->GetPosition();

	// ���� �������� ���� Ÿ���� ��ġ�̴�.
	Transform* targetTransform = m_target->GetComponent<Transform>();
	m_desitinaiton = targetTransform->GetPosition();

	// ���� �Ÿ����̸� �������� �����Ѵ�.  
	m_prevDistance = (m_desitinaiton - position).LengthSquared();

	assert(m_prevDistance >= 0.f);

	// �̵����� 
	m_direct = (m_desitinaiton - position).GetNormalize();
}
