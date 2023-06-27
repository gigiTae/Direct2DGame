#include "GameProcessPCH.h"
#include "Player.h"
#include "InputManager.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Transform.h"
#include "RigidBody.h"

Player::Player(const string& _name)
	:GameObject(_name)
	,m_moveSpeed(0.f)
{
}

Player::~Player()
{
}

void Player::Initalize()
{
	Transform* transform = CreateComponent<Transform>();
	transform->SetPosition(Vector2(100.f, 100.f));
	transform->SetScale(Vector2(100.f, 100.f));

	m_moveSpeed = 500.f;

	constexpr Vector2 SCALE(50.f, 100.f);

	BoxCollider* boxCollider = CreateComponent<BoxCollider>();
	boxCollider->SetRotatble(true);
	boxCollider->SetScale(Vector2(1.f,40.f));

	CircleCollider* circleCollider = CreateComponent<CircleCollider>();
	circleCollider->SetRadius(100.f);

	RigidBody* rigidBody = CreateComponent<RigidBody>();

}

void Player::Update(float _deltaTime, InputManager* _inputManager)
{
}

void Player::FixedUpdate(float _fixedDeltaTime, InputManager* _inputManager)
{
	RigidBody* rigid = GetComponent<RigidBody>();
	float rotation = GetComponent<Transform>()->GetRotation();

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
	Vector2 position = GetComponent<Transform>()->GetPosition();
	Vector2 v = GetComponent<RigidBody>()->GetVelocity();
	_d2DRenderer->DrawLine(position, position + v);

}
