#include "GameProcessPCH.h"
#include "Component.h"

// typeid -> type_info ��ȯ�Ѵ�.
// �ڷ���, Ŭ����, �Լ�, ��ü��
Component::Component(CALL_ORDER _callOrder, string _name)
	:m_name(_name)
	,m_callOrder(_callOrder)
	,m_gameObject(nullptr)
{
	
}

Component::~Component()
{

}
