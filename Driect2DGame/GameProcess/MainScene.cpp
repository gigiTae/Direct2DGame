#include "GameProcessPCH.h"
#include "MainScene.h"
#include "Player.h"
#include "Box.h"
#include "Line.h"
#include "CollisionManager.h"
#include "Point.h"
#include "Transform.h"

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
}
