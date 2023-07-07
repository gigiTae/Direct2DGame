#include "GameProcessPCH.h"
#include "MainScene.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "FileManager.h"
#include "GameObject.h"
#include "BoxRender.h"
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

	GameObject* ui = new GameObject("ui",GetManagerSet());

	ui->CreateComponent<Transform>()->SetScale(Vector2(100.f, 100.f));
	ui->CreateComponent<UI>();
	ui->CreateComponent<BoxRender>();

	AddObject(ui, OBJECT_TYPE::UI);
}
