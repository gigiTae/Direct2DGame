#include "GameProcessPCH.h"
#include "MainScene.h"
#include "Player.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Enter()
{
	Player* player = new Player();
	player->Initalize();

	AddObject(player, OBJECT_TYPE::PLAYER);

}
