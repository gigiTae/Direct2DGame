#include "GameProcessPCH.h"
#include "Line.h"
#include "BoxCollider.h"
#include "Transform.h"

Line::Line()
	:GameObject(L"Line")
{
}

Line::~Line()
{
}

void Line::Initalize()
{
	CreateTransform(Vector2(0.f, 0.f), Vector2(100.f, 100.f));

	CreateBoxCollider();
	BoxCollider* boxCollider = GetBoxCollider();
	boxCollider->SetScale(Vector2(2000.f, 1.f));
	boxCollider->SetRotatble(true);
}

void Line::Update(float _deltaTime, InputManager* inputManager)
{
	Vector2 position = GetTransform()->GetPosition();
	
	position.y += _deltaTime * 200.f;

	if (position.y >= 450.f)
	{
		position.y = -450.f;
	}

	GetTransform()->SetPosition(position);
}

