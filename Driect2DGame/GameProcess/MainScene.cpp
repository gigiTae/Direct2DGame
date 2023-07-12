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
#include "BoxCollider.h"

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


	/// UI
	GameObject* frontUI = new GameObject("frontUI", GetManagerSet(), OBJECT_TYPE::FRONT_UI);
	frontUI->SetCameraAffected(false);
	frontUI->CreateComponent<Transform>()->SetPosition(Vector2(0.f, -440.f));
	frontUI->GetComponent<Transform>()->SetScale(Vector2(1920.f, 200.f));
	frontUI->CreateComponent<TextureRenderer>()->SetKey(L"FrontUI");
	frontUI->CreateComponent<UI>();
	AddObject(frontUI, OBJECT_TYPE::FRONT_UI);

	/// 컨트롤러
	GameObject* controller = new GameObject("controller", GetManagerSet(), OBJECT_TYPE::BACK_UI);
	controller->CreateComponent<Transform>()->SetPosition(Vector2(0.f, 0.f));
	controller->GetComponent<Transform>()->SetScale(Vector2(1920.f, 1080.f));
	controller->CreateComponent<UI>();
	controller->CreateComponent<Controller>();
	controller->SetCameraAffected(false);

	AddObject(controller, OBJECT_TYPE::BACK_UI);

	///

	GameObject* attaker = new GameObject("attaker", GetManagerSet(), OBJECT_TYPE::UNIT);
	Transform* attakerT = attaker->CreateComponent<Transform>();
	attakerT->SetPosition(Vector2(0.f, 0.f));
	attakerT->SetScale(Vector2(100.f, 100.f));
	attaker->CreateComponent<TextureRenderer>()->SetKey(L"attaker1");
	FlyMovement* movement = new FlyMovement();

	attaker->CreateComponent<RigidBody>();
	//marine->CreateComponent<CircleCollider>()->SetRadius(20.f);
	attaker->CreateComponent<BoxCollider>()->SetScale(Vector2(64.f, 64.f));
	attaker->CreateComponent<CircleCollider>()->SetRadius(300.f);
	attaker->CreateComponent<Unit>()->Initalize(movement);


	attaker->GetComponent<RigidBody>()->SetMass(1.f);//FLT_MAX);
	AddObject(attaker, OBJECT_TYPE::ENEMY);

   const CollisionManager* collisionMgr =GetManagerSet()->GetCollisionManager();
   collisionMgr->CheckCollisionObjectType(OBJECT_TYPE::ENEMY, OBJECT_TYPE::ENEMY);

}
