#include "GameProcessPCH.h"
#include "Point.h"
#include "BoxCollider.h"

Point::Point()
	:GameObject(L"Point")
{
}

Point::~Point()
{
}

void Point::Initalize()
{
	CreateTransform(Vector2(0.f, 0.f), Vector2(100.f, 100.f));

	CreateBoxCollider();
	BoxCollider* boxCollider = GetBoxCollider();
	boxCollider->SetScale(Vector2(1.f, 1.f));
	boxCollider->SetRotatble(false);
}

void Point::Update(float _deltaTime, InputManager* inputManager)
{
	const wstring& name = GetName();
}
