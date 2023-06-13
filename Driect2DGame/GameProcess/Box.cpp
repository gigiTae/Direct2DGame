
#include "GameProcessPCH.h"
#include "Box.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Transform.h"

Box::Box()
	:GameObject(L"Box")
{
}

Box::~Box()
{
}

void Box::Initalize()
{
	CreateTransform(Vector2(0.f, 0.f), Vector2(100.f, 100.f));

	CreateBoxCollider();
	BoxCollider* boxCollider = GetBoxCollider();
	boxCollider->SetScale(Vector2(100.f, 500.f));
	boxCollider->SetRotatble(true);

	//CreateCircleCollider();
	//CircleCollider* circleCollider = GetCircleCollider();
	//circleCollider->SetRadius(100.f);
}

void Box::Update(float _deltaTime, InputManager* inputManager)
{
	GetTransform()->AddRotation(0.01f);
}
