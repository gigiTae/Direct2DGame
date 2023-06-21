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

	for (int i = 0; i < 300; ++i)
	{
		Box* box = new Box();
		box->Initalize();

		AddObject(box, OBJECT_TYPE::MONSTER);
	}

	GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER);
}
