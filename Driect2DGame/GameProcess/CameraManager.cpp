#include "GameProcessPCH.h"
#include "CameraManager.h"

CameraManager::CameraManager()
	:m_camera(nullptr)
	,m_d2DRenderer(nullptr)
	,m_screenSize{}
{

}

CameraManager::~CameraManager()
{

}

void CameraManager::Initalize(D2DRenderer* _renderer, Vector2 _screenSize)
{
	m_screenSize = _screenSize;
	m_d2DRenderer = _renderer;
	m_camera = m_d2DRenderer->GetCamera();
}

Vector2 CameraManager::ScreenToWorld(const Vector2& _screen) const
{
	/// ī�޶� ��ǥ������ ó���� �ʿ��غ���
	Vector2 world = _screen - m_screenSize * 0.5f;
	world.y = -world.y;

	return world;
}
