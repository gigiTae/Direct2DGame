#include "GameProcessPCH.h"
#include "Component.h"

// typeid -> type_info 반환한다.
// 자료형, 클래스, 함수, 객체를 
Component::Component()
	:m_name(typeid(*this).name())
	,m_gameObject(nullptr)
{

}

Component::~Component()
{

}
