#include "GameProcessPCH.h"
#include "MainScene.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "FileManager.h"
#include "GameObject.h"
#include "BoxRenderer.h"
#include "Animator.h"
#include "TextureRenderer.h"
#include "UI.h"
#include "RigidBody.h"
#include "Unit.h"
#include "CircleCollider.h"
#include "Controller.h"
#include "FlyMovement.h"
#include "ManagerSet.h"

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


	/// 배경
	GameObject* background = new GameObject("background",GetManagerSet());
	background->CreateComponent<Transform>()->SetPosition(Vector2(0.f, 0.f));
	background->CreateComponent<TextureRenderer>()->SetKey(L"background");

	AddObject(background, OBJECT_TYPE::BACKGROUND);

	/// UI
	GameObject* frontUI = new GameObject("frontUI", GetManagerSet());
	frontUI->SetCameraAffected(false);
	frontUI->CreateComponent<Transform>()->SetPosition(Vector2(0.f, -440.f));
	frontUI->GetComponent<Transform>()->SetScale(Vector2(1920.f, 200.f));
	frontUI->CreateComponent<TextureRenderer>()->SetKey(L"FrontUI");
	frontUI->CreateComponent<UI>();
	AddObject(frontUI, OBJECT_TYPE::FRONT_UI);
	
	/// 컨트롤러
	GameObject* controller = new GameObject("controller", GetManagerSet());
	controller->CreateComponent<Transform>()->SetPosition(Vector2(0.f, 0.f));
	controller->GetComponent<Transform>()->SetScale(Vector2(1920.f, 1080.f));
	controller->CreateComponent<UI>();
	controller->CreateComponent<Controller>();
	controller->SetCameraAffected(false);

	AddObject(controller, OBJECT_TYPE::BACK_UI);

	///
	for (int i = 0; i < 2; ++i)
	{
		GameObject* marine = new GameObject("FlyingSlime", GetManagerSet());
		Transform* marineT = marine->CreateComponent<Transform>();
		marineT->SetPosition(Vector2(100.f * i, 0.f));
		marineT->SetScale(Vector2(100.f, 100.f));
		marine->CreateComponent<TextureRenderer>()->SetKey(L"river");
		FlyMovement* movement = new FlyMovement();

		marine->CreateComponent<RigidBody>();
		marine->CreateComponent<CircleCollider>()->SetRadius(20.f);

		marine->CreateComponent<Unit>()->Initalize(movement);


		if (i ==0)
		{
			marine->GetComponent<RigidBody>()->SetMass(FLT_MAX);
		}

		AddObject(marine, OBJECT_TYPE::AIR_UNIT);
		
	}


   const CollisionManager* collisionMgr =GetManagerSet()->GetCollisionManager();
   collisionMgr->CheckCollisionObjectType(OBJECT_TYPE::AIR_UNIT, OBJECT_TYPE::AIR_UNIT);

}
