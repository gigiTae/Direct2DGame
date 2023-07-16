#include "GameProcessPCH.h"
#include "Factory.h"
#include "GameObject.h"
#include "Controller.h"
#include "UnitSensor.h"
#include "Unit.h"
#include "UnitAttack.h"
#include "BarUI.h"
#include "UnitMovement.h"
#include "FlyMovement.h"


SC::Factory::Factory(const ManagerSet* _managerSet)
	:m_managerSet(_managerSet)
{

}

SC::Factory::~Factory()
{

}

GameObject* SC::Factory::CreateFrontUI()
{
	TransformInfo info{};
	info.position = Vector2(0.f, -440.f);
	info.scale = Vector2(1920.f, 200.f);
	info.rotation = 0.f;

	GameObject* object = CreateGameObject("frontUI"
		, m_managerSet, OBJECT_TYPE::FRONT_UI,info);
	
	CreateTextureRenderer(object, L"FrontUI");
	CreateUI(object);

	object->SetCameraAffected(false);

	return object;
}

GameObject* SC::Factory::CreateController()
{
	TransformInfo info(Vector2::Zero, Vector2(1920.f, 1080.f));
	
	GameObject* controller = CreateGameObject("controller"
		, m_managerSet, OBJECT_TYPE::BACK_UI, info);

	controller->SetCameraAffected(false);

	CreateUI(controller);
	controller->CreateComponent<Controller>();

	return controller;
}

GameObject* SC::Factory::CreateFlySlime(Vector2 _position)
{
	TransformInfo transformInfo(_position, Vector2(100.f, 100.f));

	GameObject* flySlime = CreateGameObject("FlySlime", m_managerSet
		, OBJECT_TYPE::ENEMY,transformInfo);

	CreateTextureRenderer(flySlime, L"FlySlime");
	CreateRigidBody(flySlime,1.f);

	BoxColliderInfo boxInfo(Vector2::Zero, Vector2(32.f, 32.f));
	CreateBoxCollider(flySlime, boxInfo);
	
	CircleInfo circleInfo(Vector2::Zero, 150.f);
	CreateCircleColldier(flySlime, circleInfo);

	flySlime->CreateComponent<UnitSensor>();
	flySlime->CreateComponent<FlyMovement>();
	flySlime->CreateComponent<UnitAttack>();

	UnitInfomaiton info{};
	info.attackSpeed = 0.5f;
	info.maxHP = 100.f;
	info.currentHP = 100.f;
	info.attackRange;
	info.attackType = ATTACK_TYPE::GUN;
	info.state = UNIT_STATE::HOLD;
	flySlime->CreateComponent<Unit>()->Initalize(info);


	BarUIInfo barInfo{};
	barInfo.barLength = 1.f;
	barInfo.barScale = Vector2(50.f, 10.f);
	barInfo.innerBarOffset = Vector2(-10.f, -5.f);
	barInfo.positionOffset = Vector2(0.f,50.f);
	barInfo.edgeColor = D2D1::ColorF(ColorF::White,0.5f);
	barInfo.innerFillBarColor = ColorF(ColorF::Red);
	barInfo.innerEmptyBarColor = ColorF(ColorF::White);

	flySlime->CreateComponent<BarUI>()->SetBar(barInfo);

	return flySlime;
}
