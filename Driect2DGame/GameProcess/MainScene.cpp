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

	GameObject* effect = new GameObject("effect", GetManagerSet(), OBJECT_TYPE::BACKGROUND);
	effect->CreateComponent<Transform>();
	effect->CreateComponent<BackgroundEffect>()->SetEffect(2000.f, 0.0001f);
	AddObject(effect);

	/// 컨트롤러
	GameObject* controller = factory.CreateController();
	AddObject(controller);

	for (int i = 0; i <	1; ++i)
	{
		GameObject* attaker = factory.CreateFlySlime(Vector2(-1900.f, 250.f));
		AddObject(attaker);
	}

   const CollisionManager* collisionMgr =GetManagerSet()->GetCollisionManager();
   collisionMgr->CheckCollisionObjectType(OBJECT_TYPE::ENEMY, OBJECT_TYPE::ENEMY);
}
