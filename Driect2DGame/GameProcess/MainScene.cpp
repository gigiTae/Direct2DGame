#include "GameProcessPCH.h"
#include "MainScene.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Movement.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Enter()
{
	GameObject* player = new GameObject("player");
	player->CreateComponent<Transform>();
	Transform* transform = player->GetComponent<Transform>();
	transform->SetPosition(Vector2(100.f, 100.f));
	transform->SetRotation(0.f);
	transform->SetScale(Vector2(100.f, 100.f));
	player->CreateComponent<Movement>();
	BoxCollider* boxCollider = player->CreateComponent<BoxCollider>();
	boxCollider->SetScale(Vector2(100.f, 100.f));
	boxCollider->SetRotatble(true);

	AddObject(player, OBJECT_TYPE::PLAYER);

	GameObject* playerArm = new GameObject("player");
	playerArm->CreateComponent<Transform>();
	Transform* transform1 = playerArm->GetComponent<Transform>();
	
	transform1->SetOffset(Vector2(65.f, 0.f));
	transform1->SetOffset(1.f);
	transform1->SetScale(Vector2(100.f, 100.f));

	BoxCollider* boxCollider1 = playerArm->CreateComponent<BoxCollider>();
	boxCollider1->SetScale(Vector2(10.f, 50.f));
	boxCollider1->SetRotatble(true);

	AddObject(playerArm, OBJECT_TYPE::PLAYER);

	player->AddChild(playerArm);

	GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::PLAYER);
}
