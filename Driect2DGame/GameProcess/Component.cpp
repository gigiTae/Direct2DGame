#include "GameProcessPCH.h"
#include "Component.h"

// typeid -> type_info 반환한다.
// 자료형, 클래스, 함수, 객체를
Component::Component(CALL_ORDER _callOrder, string _name)
	:m_name(_name)
	,m_callOrder(_callOrder)
	,m_gameObject(nullptr)
{
	
}

Component::~Component()
{

}
