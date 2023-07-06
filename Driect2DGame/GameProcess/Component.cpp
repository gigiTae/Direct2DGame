#include "GameProcessPCH.h"
#include "Component.h"
#include "GameObject.h"
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

const PathManager* Component::GetPathManager() const
{
	return m_gameObject->GetPathManager();
}

const InputManager* Component::GetInputManager() const
{
	return m_gameObject->GetInputManager();
}

const TimeManager* Component::GetTimeManager() const
{
	return m_gameObject->GetTimeManager();
}

const SceneManager* Component::GetSceneManager() const
{
	return m_gameObject->GetSceneManager();
}

const UIManager* Component::GetUIManager() const
{
	return m_gameObject->GetUIManager();
}

const CollisionManager* Component::GetCollisionManager() const
{
	return m_gameObject->GetCollisionManager();
}
