#include "GameProcessPCH.h"
#include "Player.h"
#include "InputManager.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Transform.h"

Player::Player(const wstring& _name)
	:GameObject(_name)
	,m_moveSpeed(0.f)
{
}

Player::~Player()
{
}

void Player::Initalize()
{
	CreateTransform(Vector2(100.f, 100.f), Vector2(100.f, 100.f));
	m_moveSpeed = 500.f;

	CreateBoxCollider();
	BoxCollider* boxCollider = GetBoxCollider();
	boxCollider->SetScale(Vector2(100.f, 100.f));

	CreateCircleCollider();
	CircleCollider* circleCollider = GetCircleCollider();
	circleCollider->SetRadius(200.f);
}

void Player::Update(float _deltaTime, InputManager* inputManager)
{
	Vector2 addPosition{};
	
	// 키입력에 따라서 움직이자
	if (inputManager->IsKeyState(KEY::W, KEY_STATE::HOLD))
	{
		addPosition.y -= 1;
	}
	if (inputManager->IsKeyState(KEY::S, KEY_STATE::HOLD))
	{
		addPosition.y += 1;
	}
	if (inputManager->IsKeyState(KEY::D, KEY_STATE::HOLD))
	{
		addPosition.x += 1;
	}
	if (inputManager->IsKeyState(KEY::A, KEY_STATE::HOLD))
	{
		addPosition.x -= 1;
	}

	addPosition.Normalize();

	// 플레이어 위치 조정
	Vector2 playerPosition = GetTransform()->GetPosition();
	playerPosition += addPosition * m_moveSpeed * _deltaTime;
	GetTransform()->SetPosition(playerPosition);

}

void Player::Finalize()
{
	DestroyAllComponent();

}
