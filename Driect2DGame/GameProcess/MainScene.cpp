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
#include "TextureRenderer.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Enter()
{
	LoadSceneResources(L"MainScene");

	GameObject* player = new GameObject("player");
	player->CreateComponent<Transform>();
	Transform* transform = player->GetComponent<Transform>();
	transform->SetPosition(Vector2(0.f, 0.f));
	transform->SetRotation(0.f);
	transform->SetScale(Vector2(50.f, 100.f));
	player->CreateComponent<Movement>();
	player->CreateComponent<BoxRender>();
	player->CreateComponent<CircleCollider>()->SetRadius(10.f);
	player->GetComponent<CircleCollider>()->SetOffset(Vector2(0.f, 100.f));
	player->CreateComponent<TextureRenderer>()->SetKey(L"car");

	AddObject(player, OBJECT_TYPE::PLAYER);


	GameObject* player1 = new GameObject("player");
	player1->CreateComponent<Transform>();
	Transform* transform1 = player1->GetComponent<Transform>();
	transform1->SetPosition(Vector2(0.f, 0.f));
	transform1->SetRotation(0.f);
	transform1->SetScale(Vector2(100.f, 100.f));
	player1->CreateComponent<BoxRender>();
	player1->CreateComponent<CircleCollider>()->SetRadius(10.f);
	player1->GetComponent<CircleCollider>()->SetOffset(Vector2(0.f, 100.f));

	AddObject(player1, OBJECT_TYPE::PLAYER);
	player1->Destory(15.f);


	GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::PLAYER);
}
