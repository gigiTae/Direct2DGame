#include "GameProcessPCH.h"
#include "UnitAttack.h"
#include "Unit.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Transform.h"
#include "TextureRenderer.h"
#include "ShootBullet.h"

UnitAttack::UnitAttack()
	:MonoBehaviour(typeid(this).name())
	,m_unit(nullptr)
	,m_attackType(ATTACK_TYPE::NONE)
{

}

UnitAttack::~UnitAttack()
{

}

void UnitAttack::Update(float _deltaTime)
{
	m_attackCoolTime += _deltaTime;

	if (m_attackCoolTime >= m_attackSpeed)
	{
		m_attackCoolTime = m_attackSpeed;
	}
}

void UnitAttack::Attack(GameObject* _target)
{
	if (m_attackCoolTime >= m_attackSpeed)
	{
		m_attackCoolTime -= m_attackSpeed;
		// 공격타입에따라서 여러가기 공격이 나간다.
		switch (m_attackType)
		{
			case ATTACK_TYPE::NONE:
				break;
			case ATTACK_TYPE::KNIFE:
			{

			}
			break;
			case ATTACK_TYPE::MAGIC:
			{

			}
			break;
			case ATTACK_TYPE::GUN:
			{
				Shoot(_target);
			}
			break;
			default:
				break;
		}

	}
}

void UnitAttack::Start()
{
	m_unit = GetComponent<Unit>();
	m_attackType = m_unit->GetUnitInfomation().attackType;
	m_attackSpeed = m_unit->GetUnitInfomation().attackSpeed;

}



void UnitAttack::Shoot(GameObject* _target)
{
	Transform* transform = GetComponent<Transform>();
	
	Vector2 unitPos = transform->GetPosition();
	
	// 총알 생성
	GameObject* bullet = new GameObject("bullet", GetManagerSet(),OBJECT_TYPE::ATTACK_EFFECT);

	bullet->CreateComponent<Transform>()->SetPosition(unitPos);
	bullet->CreateComponent<TextureRenderer>()->SetKey(L"attack1");
	bullet->CreateComponent<ShootBullet>()->Shoot(_target, 1000.f);

	const SceneManager* sceneMgr = GetSceneManager();
	sceneMgr->RegisterObject(bullet);
}
