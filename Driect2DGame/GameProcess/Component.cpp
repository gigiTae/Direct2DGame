#include "GameProcessPCH.h"
#include "Component.h"

// typeid -> type_info ��ȯ�Ѵ�.
// �ڷ���, Ŭ����, �Լ�, ��ü�� 
Component::Component()
	:m_name(typeid(*this).name())
	,m_gameObject(nullptr)
{

}

Component::~Component()
{

}
