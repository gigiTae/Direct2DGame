#include "GameProcessPCH.h"
#include "MainScene.h"
#include "CollisionManager.h"
#include "FileManager.h"
#include "GameObject.h"
#include "ManagerSet.h"
#include "Factory.h"
#include "Transform.h"
#include "TextureRenderer.h"
#include "BackgroundEffect.h"

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

	SC::Factory factory(GetManagerSet());
	

	/// 컨트롤러
	GameObject* controller = factory.CreateController();
	AddObject(controller);

	for (int i = 0; i <	2; ++i)
	{
		GameObject* attaker = factory.CreateFlySlime(Vector2(0.f+ i, 0.f));
		AddObject(attaker);
	}

   const CollisionManager* collisionMgr =GetManagerSet()->GetCollisionManager();
   collisionMgr->CheckCollisionObjectType(OBJECT_TYPE::ENEMY, OBJECT_TYPE::ENEMY);
}
