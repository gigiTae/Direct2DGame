#include "GameProcessPCH.h"
#include "Movement.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "CircleCollider.h"
#include "Transform.h"
#include "TextureRenderer.h"

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
	const InputManager* inputManager = GetInputManager();
	const SceneManager* sceneManager = GetSceneManager();

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
	if (inputManager->IsKeyState(KEY::T, KEY_STATE::TAP) && GetGameObject()->GetParent() == nullptr)
	{
		GameObject* monster = new GameObject("monsterhhh", GetManagerSet());
		monster->CreateComponent<Transform>()->SetPosition(Vector2(1.f, 100.f));
		monster->CreateComponent<TextureRenderer>()->SetKey(L"map");
		monster->Destory(5.f);

		sceneManager->RegisterObject(monster, OBJECT_TYPE::MONSTER, 1.f);
	}
	direct = direct.GetNormalize() * m_speed * _deltaTime;
	transform->AddPosition(direct);
}
