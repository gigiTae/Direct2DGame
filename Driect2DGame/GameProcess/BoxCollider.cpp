#include "GameProcessPCH.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider()
	:m_offset{}
	,m_position{}
	,m_rotation(0.f)
	,m_scale{}
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::DebugRender(D2DRenderer* _d2DRenderer)
{
}
