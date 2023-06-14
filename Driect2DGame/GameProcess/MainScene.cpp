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

	for (int i = 0; i < 100; ++i)
	{
		Point* point = new Point();
		point->Initalize();
		point->GetTransform()->SetPosition(Vector2(0.f,-500.f + i * 10.f));
		AddObject(point, OBJECT_TYPE::MONSTER);
	}

	for (int i = 0; i < 200; ++i)
	{
		Point* point = new Point();
		point->Initalize();
		point->GetTransform()->SetPosition(Vector2(i*10.f - 1000.f, 0.f));
		AddObject(point, OBJECT_TYPE::MONSTER);
	}

	Box* box = new Box();
	box->Initalize();
	AddObject(box, OBJECT_TYPE::MONSTER);

	Line* line = new Line();
	line->Initalize();
	AddObject(line, OBJECT_TYPE::MONSTER);

	GetCollisionManager()->CheckCollisionObjectType(OBJECT_TYPE::PLAYER, OBJECT_TYPE::MONSTER);
}
