#include "GameProcessPCH.h"
#include "MainScene.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "Movement.h"
#include "BoxRender.h"

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
	transform->SetPosition(Vector2(0.f, 0.f));
	transform->SetRotation(0.f);
	transform->SetScale(Vector2(100.f, 100.f));
	player->CreateComponent<Movement>();
	player->CreateComponent<BoxRender>();
	player->CreateComponent<CircleCollider>()->SetRadius(10.f);
	player->GetComponent<CircleCollider>()->SetOffset(Vector2(0.f, 100.f));
	

	AddObject(player, OBJECT_TYPE::PLAYER);
	
	GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::PLAYER);
}
