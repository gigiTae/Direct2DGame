#include "GameProcessPCH.h"
#include "MainScene.h"
#include "Player.h"
#include "CollisionManager.h"
#include "Transform.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Enter()
{
	for (int i = 0; i < 100; ++i)
	{
		Player* player = new Player(L"player");
		player->Initalize();
		AddObject(player, OBJECT_TYPE::PLAYER);
	}
	GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::PLAYER);
}
