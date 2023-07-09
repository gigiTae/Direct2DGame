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
#include "Unit.h"
#include "Controller.h"

MainScene::MainScene()
{
}    

MainScene::~MainScene()
{
}

void MainScene::Enter()
{
	/// ���ҽ� �ε�
	LoadSceneResources(L"MainScene");


	/// ���
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
	
	/// ��Ʈ�ѷ�
	GameObject* controller = new GameObject("controller", GetManagerSet());
	controller->CreateComponent<Transform>()->SetPosition(Vector2(0.f, 0.f));
	controller->GetComponent<Transform>()->SetScale(Vector2(1920.f, 1080.f));
	controller->CreateComponent<UI>();
	controller->CreateComponent<Controller>();
	controller->SetCameraAffected(false);

	AddObject(controller, OBJECT_TYPE::BACK_UI);

	/// 
	for (int i = 0; i < 10; ++i)
	{
		GameObject* marine = new GameObject("marine", GetManagerSet());
		Transform* marineT =marine->CreateComponent<Transform>();
		marineT->SetPosition(Vector2(100.f * i, 0.f));
		marineT->SetScale(Vector2(100.f, 100.f));
		marine->CreateComponent<TextureRenderer>()->SetKey(L"FlySlime");
		marine->CreateComponent<Unit>();

		AddObject(marine, OBJECT_TYPE::GROUND_UNIT);
	}
}
