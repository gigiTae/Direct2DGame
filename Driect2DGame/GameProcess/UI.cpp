#include "GameProcessPCH.h"
#include "UI.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "CameraManager.h"

UI::UI():Component(CALL_ORDER::UI,typeid(this).name())
	,m_LBtnDown(false)
	,m_mouseOn(false)
{

}

UI::~UI()
{

}

void UI::Render(D2DRenderer* _d2DRenderer)
{
	Transform* transform = GetComponent<Transform>();
	Vector2 position = transform->GetPosition();
	Vector2 scale = transform->GetScale();

	Vector2 leftTop{ position.x - scale.x * 0.5f , position.y + scale.y * 0.5f };
	Vector2 rightBottom{ position.x + scale.x * 0.5f, position.y - scale.y * 0.5f };

	if (m_LBtnDown)
	{
		_d2DRenderer->DrawRectangle(leftTop, rightBottom, D2D1::ColorF::Red);
	}
	else
	{
		_d2DRenderer->DrawRectangle(leftTop, rightBottom, D2D1::ColorF::Green);
	}
	
}

void UI::LateUpdate(float _deltaTime)
{
	/// 마우스 온 체크 
	const InputManager* input = GetInputManager();
	Transform* transform = GetComponent<Transform>();
	
	Vector2 mousePosition = input->GetMousePosition();
	Vector2 scale = transform->GetScale();
	Vector2 position = transform->GetPosition();

	Vector2 Min = position - scale * 0.5f;
	Vector2 Max = position + scale * 0.5f;

	if (Min.x <= mousePosition.x && Min.y <= mousePosition.y
		&& Max.x >= mousePosition.x && Max.y >= mousePosition.y)
	{
		m_mouseOn = true;
	}
	else
	{
		m_mouseOn = false;
	}
}
