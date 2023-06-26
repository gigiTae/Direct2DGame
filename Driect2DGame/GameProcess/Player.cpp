#include "GameProcessPCH.h"
#include "Player.h"
#include "InputManager.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Transform.h"
#include "RigidBody.h"

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

	constexpr Vector2 SCALE(50.f, 100.f);

	CreateBoxCollider();
	BoxCollider* boxCollider = GetBoxCollider();
	boxCollider->SetRotatble(true);
	boxCollider->SetScale(Vector2(1.f,40.f));

	CreateCircleCollider();
	GetCircleCollider()->SetRadius(100.f);

	CreateRigidBody(1.f, SCALE);
}

void Player::Update(float _deltaTime, InputManager* _inputManager)
{
}

void Player::FixedUpdate(float _fixedDeltaTime, InputManager* _inputManager)
{
	RigidBody* rigid = GetRigidBody();
	float rotation = GetTransform()->GetRotation();

	if (_inputManager->IsKeyState(KEY::W, KEY_STATE::HOLD))
	{
		Vector2 force(0.f, 1000.f);
		force = Vector2::RotateRadian(force, Vector2::Zero, rotation);
		rigid->AddForce(force);
	}
	if (_inputManager->IsKeyState(KEY::S, KEY_STATE::HOLD))
	{
		Vector2 force(0.f, -500.f);
		force = Vector2::RotateRadian(force, Vector2::Zero, rotation);
		rigid->AddForce(force);
	}
	if (_inputManager->IsKeyState(KEY::D, KEY_STATE::HOLD))
	{
		rigid->AddToque(-1500.f);
	}
	if (_inputManager->IsKeyState(KEY::A, KEY_STATE::HOLD))
	{
		rigid->AddToque(1500.f);
	}
}

void Player::Finalize()
{
	DestroyAllComponent();

}

void Player::Render(D2DRenderer* _d2DRenderer)
{
	Vector2 position = GetTransform()->GetPosition();
	Vector2 v = GetRigidBody()->GetVelocity();
	_d2DRenderer->DrawLine(position, position + v);

}
