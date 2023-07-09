#include "GameProcessPCH.h"
#include "Unit.h"
#include "Transform.h"
#include "GameObject.h"

Unit::Unit()
	:MonoBehaviour(typeid(this).name())
	,m_isSelect(false)
	,m_state(UNIT_STATE::HOLD)
{

}

Unit::~Unit()
{

}

void Unit::PreRender(D2DRenderer* _d2DRenderer)
{
	if (!m_isSelect)
	{
		return;
	}

	Transform* transform = GetComponent<Transform>();
	Vector2 position = transform->GetPosition();
	Vector2 scale = transform->GetScale();
	scale.y *= 0.5f;
	position.y -= scale.y;

	_d2DRenderer->DrawEllipse(position, scale, D2D1::ColorF::Green);

}

void Unit::Update(float _deltaTime)
{

}
