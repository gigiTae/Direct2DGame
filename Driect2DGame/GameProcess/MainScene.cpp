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

	for (int i = 0; i < 3; ++i)
	{
		GameObject* ui = new GameObject("ui", GetManagerSet());

		ui->CreateComponent<Transform>()->SetScale(Vector2(500.f, 500.f));
		ui->GetComponent<Transform>()->SetPosition(Vector2(100.f*i, 10.f*i));
		ui->CreateComponent<UI>();
		ui->CreateComponent<TextureRenderer>()->SetKey(L"dsd");

		GameObject* ui4 = new GameObject("ui", GetManagerSet());

		ui4->CreateComponent<Transform>()->SetScale(Vector2(64.f, 64.f));
		ui4->GetComponent<Transform>()->SetPosition(Vector2(-20.f, -10.f));
		ui4->CreateComponent<UI>();

		GameObject* ui2 = new GameObject("ui", GetManagerSet());

		ui2->CreateComponent<Transform>()->SetScale(Vector2(64.f, 64.f));
		ui2->GetComponent<Transform>()->SetPosition(Vector2(50.f, 0.f));
		ui2->CreateComponent<UI>();

		GameObject* ui3 = new GameObject("ui", GetManagerSet());

		ui3->CreateComponent<Transform>()->SetScale(Vector2(64.f, 64.f));
		ui3->GetComponent<Transform>()->SetOffset(Vector2(100.f, 100.f));
		ui3->CreateComponent<UI>();
		ui3->CreateComponent<TextureRenderer>()->SetKey(L"car");

		ui->AddChild(ui2);
		ui->AddChild(ui3);
		ui->AddChild(ui4);

		if (i == 1)
			AddObject(ui, OBJECT_TYPE::BACK_UI);
		else
			AddObject(ui, OBJECT_TYPE::FRONT_UI);
	}
}
