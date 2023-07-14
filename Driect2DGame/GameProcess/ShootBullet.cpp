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
	,m_shootSpeed(0.f)
	,m_target(nullptr)
{

}

ShootBullet::~ShootBullet()
{

}

void ShootBullet::Update(float _deltaTime)
{
	// 타겟이 사라진경우 총알을 파괴한다.
	if ( m_target == nullptr || !m_target->IsAlive())
	{
		m_target = nullptr;
	}

	Transform* transform = GetComponent<Transform>();
	
	// 총알이 이동거리만큼 이동한다.
	Vector2 moveDistance = m_direct * _deltaTime * m_shootSpeed;
	transform->AddPosition(moveDistance);

	Vector2 position = transform->GetPosition();
	
	// 거리의 제곱이 일정거리 이하면 총알을 삭제하고 타겟에게 대미지를 준다.
	float dist = (position - m_desitinaiton).LengthSquared();

	if (dist < 25.f && GetGameObject()->GetObjectState() == OBJECT_STATE::ALIVE)
	{
		GetGameObject()->Destory();
		GameObject* effect = new GameObject("effect", GetManagerSet(), OBJECT_TYPE::ATTACK_EFFECT);
		effect->CreateComponent<Transform>()->SetPosition(position);
		effect->CreateComponent<Animator>()->CreateAnimation(L"hitAnimation1", L"hitEffect1", Vector2::Zero, Vector2(32.f, 32.f), Vector2(32.f, 0.f), 0.1f, 3);
		effect->GetComponent<Animator>()->Play(L"hitAnimation1", false);

		GetManagerSet()->GetSceneManager()->RegisterObject(effect);
		effect->Destory(0.3f);
		//  TODO : _target-> 대미지를 가한다 
	
		if (m_target != nullptr)
			m_target->GetComponent<Unit>()->TakeDamage(10.f);
	}

}


void ShootBullet::Shoot(GameObject* _target, float _speed)
{
	m_target = _target;
	m_shootSpeed = _speed;

	// 현재 발사위치
	Transform* transform = GetComponent<Transform>();
	Vector2 position = transform->GetPosition();

	// 최종 목적지는 현재 타겟의 위치이다.
	Transform* targetTransform = m_target->GetComponent<Transform>();
	m_desitinaiton = targetTransform->GetPosition();

	// 이동방향 
	m_direct = (m_desitinaiton - position).GetNormalize();
}
