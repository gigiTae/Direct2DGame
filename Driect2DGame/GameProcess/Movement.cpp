#include "GameProcessPCH.h"
#include "Movement.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "TimeManager.h"

Movement::Movement()
	:MonoBehaviour(typeid(this).name())
	,m_speed(100.f)
{
}

Movement::~Movement()
{

}

void Movement::Update(float _deltaTime)
{
	Vector2 direct{};
	Transform* transform = GetComponent<Transform>();
	const TimeManager* timeManager = GetManager<TimeManager>();
	const InputManager* inputManager = GetManager<InputManager>();

	if (inputManager->IsKeyState(KEY::UP,KEY_STATE::HOLD))
	{
		direct.y++;
	}
	if (inputManager->IsKeyState(KEY::DOWN, KEY_STATE::HOLD))
	{
		direct.y--;
	}
	if (inputManager->IsKeyState(KEY::RIGHT, KEY_STATE::HOLD))
	{
		direct.x++;
	}
	if (inputManager->IsKeyState(KEY::LEFT, KEY_STATE::HOLD))
	{
		direct.x--;
	}
	if (inputManager->IsKeyState(KEY::SPACE, KEY_STATE::HOLD))
	{
		transform->AddRotation(m_speed * _deltaTime*0.01f);
	}
	if (inputManager->IsKeyState(KEY::A, KEY_STATE::HOLD))
	{
		float offset = transform->GetRotationOffset();
		offset += 0.0001f;
		transform->SetOffset(offset);
	}
	if (inputManager->IsKeyState(KEY::S, KEY_STATE::HOLD))
	{
		float offset = transform->GetRotationOffset();
		offset -= 0.0001f;
		transform->SetOffset(offset);
	}

	direct = direct.GetNormalize() * m_speed * _deltaTime;
	transform->AddPosition(direct);

}
