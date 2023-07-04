#include "GameProcessPCH.h"
#include "MainScene.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "FileManager.h"
#include "GameObject.h"
#include "Movement.h"
#include "BoxRender.h"
#include "Animator.h"
#include "TextureRenderer.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Enter()
{
	/// 리소스 로드
	LoadSceneResources(L"MainScene");

	/// 플레이어 오브젝트 추가 
	GameObject* player = new GameObject("player");
	player->CreateComponent<Transform>();
	Transform* transform = player->GetComponent<Transform>();
	transform->SetPosition(Vector2(0.f, 0.f));
	transform->SetRotation(0.f);
	transform->SetScale(Vector2(50.f, 100.f));
	player->CreateComponent<Movement>();
	player->CreateComponent<BoxRender>();
	player->CreateComponent<CircleCollider>()->SetRadius(50.f);
	Animator* playerAnimator = player->CreateComponent<Animator>();
	playerAnimator->CreateAnimation(L"bossWalk", L"boss", Vector2::Zero, Vector2(225.f, 225.f), Vector2(225.f, 0.f), 0.1f, 4);
	playerAnimator->Play(L"bossWalk", true);

	GameObject* tmp = player;
	for (int i = 0; i < 10; ++i)
	{
		GameObject* car = new GameObject("car");
		car->CreateComponent<Transform>();
		Transform* transform1 = car->GetComponent<Transform>();
		transform1->SetOffset(Vector2(-60.f, -10.f));
		transform1->SetOffset(0.5f);
		car->CreateComponent<CircleCollider>()->SetRadius(50.f);
		car->CreateComponent<TextureRenderer>()->SetKey(L"car");
		car->CreateComponent<Movement>();
		tmp->AddChild(car);
		tmp = car;
	}

	AddObject(player, OBJECT_TYPE::PLAYER);

	GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::PLAYER);
}
