#include "GameProcessPCH.h"
#include "MainScene.h"
#include "Player.h"
#include "Box.h"
#include "CollisionManager.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Enter()
{
	Player* player = new Player(L"player");
	player->Initalize();

	AddObject(player, OBJECT_TYPE::PLAYER);

	Box* box = new Box();
	box->Initalize();
	AddObject(box, OBJECT_TYPE::MONSTER);

	GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER);
}
