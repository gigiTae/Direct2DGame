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
#include "UnitMovement.h"
#include "UnitAttack.h"
#include "UnitSensor.h"

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
	AddObject(frontUI);

	/// 컨트롤러
	GameObject* controller = new GameObject("controller", GetManagerSet(), OBJECT_TYPE::BACK_UI);
	controller->CreateComponent<Transform>()->SetPosition(Vector2(0.f, 0.f));
	controller->GetComponent<Transform>()->SetScale(Vector2(1920.f, 1080.f));
	controller->CreateComponent<UI>();
	controller->CreateComponent<Controller>();
	controller->SetCameraAffected(false);

	AddObject(controller);

	for (int i = 0; i < 2; ++i)
	{
		GameObject* attaker = new GameObject("attaker", GetManagerSet(), OBJECT_TYPE::ENEMY);
		Transform* attakerT = attaker->CreateComponent<Transform>();
		attakerT->SetPosition(Vector2(-400.f + 400.f*i, 0.f));
		attakerT->SetScale(Vector2(100.f, 100.f));
		attaker->CreateComponent<TextureRenderer>()->SetKey(L"attaker1");

		attaker->CreateComponent<RigidBody>();
		attaker->GetComponent<RigidBody>()->SetMass(1.f);//FLT_MAX);
		attaker->CreateComponent<BoxCollider>()->SetScale(Vector2(64.f, 64.f));
		attaker->CreateComponent<CircleCollider>()->SetRadius(300.f);

		attaker->CreateComponent<UnitSensor>();
		attaker->CreateComponent<FlyMovement>();
		attaker->CreateComponent<UnitAttack>();

		UnitInfomaiton info{};
		info.attackSpeed = 0.5f;
		info.attackType = ATTACK_TYPE::GUN;
		info.state = UNIT_STATE::HOLD;
		attaker->CreateComponent<Unit>()->Initalize(info);


		AddObject(attaker);
	}

   const CollisionManager* collisionMgr =GetManagerSet()->GetCollisionManager();
   collisionMgr->CheckCollisionObjectType(OBJECT_TYPE::ENEMY, OBJECT_TYPE::ENEMY);

}
