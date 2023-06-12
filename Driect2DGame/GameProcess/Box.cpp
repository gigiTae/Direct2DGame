
#include "GameProcessPCH.h"
#include "Box.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

Box::Box()
	:GameObject(L"Box")
{
}

Box::~Box()
{
}

void Box::Initalize()
{
	CreateTransform(Vector2(500.f, 500.f), Vector2(100.f, 100.f));

	CreateBoxCollider();
	BoxCollider* boxCollider = GetBoxCollider();
	boxCollider->SetScale(Vector2(100.f, 100.f));

	CreateCircleCollider();
	CircleCollider* circleCollider = GetCircleCollider();
	circleCollider->SetRadius(200.f);
}

void Box::Update(float _deltaTime, InputManager* inputManager)
{
}

void Box::Finalize()
{
}
