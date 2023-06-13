#include "GameProcessPCH.h"
#include "Transform.h"

Transform::Transform()
	:m_position{}
	,m_rotation(0.f)
	,m_scale{}
{
}

Transform::~Transform()
{
}

void Transform::FinalUpdate()
{
	// 각도값을 조정
	if (m_rotation >= FMath::TwoPI)
	{
		m_rotation -= FMath::TwoPI;
	}
	
	if (m_rotation <= -FMath::TwoPI)
	{
		m_rotation += FMath::TwoPI;
	}
}
