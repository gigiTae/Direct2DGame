#include "GameProcessPCH.h"
#include "CameraManager.h"
#include "InputManager.h"

CameraManager::CameraManager()
	:m_camera(nullptr)
	,m_d2DRenderer(nullptr)
	,m_screenSize{}
	,m_inputManager(nullptr)
	,m_moveSpeed(0.f)
{

}

CameraManager::~CameraManager()
{

}

void CameraManager::Initalize(D2DRenderer* _renderer, Vector2 _screenSize, InputManager* _inputManager)
{
	m_screenSize = _screenSize;
	m_d2DRenderer = _renderer;
	m_camera = m_d2DRenderer->GetCamera();
	m_inputManager = _inputManager;

	m_moveSpeed = 300.f;

	m_camera->ZoomCamera(Vector2(-0.5f, -0.5f));
}

void CameraManager::Update(float _deltaTime)
{
	///// 카메라 이동
	//Vector2 screenPosition = m_inputManager->GetScreendMousePosition();

	///// 1. 맵사이즈 제한해서 카메라 움직이기
	///// 2. 특정영역에 마우스가 있으면 카메라 움직이기 
	//Vector2 mouseScreenPos = m_inputManager->GetScreendMousePosition();

	//Vector2 direction = Vector2::Zero;
	//// 상단 이동
	//if (mouseScreenPos.y <= 50.f)
	//{
	//	++direction.y;
	//}
	//// 하단 이동
	//if (mouseScreenPos.y >=  m_screenSize.y-50.f)
	//{
	//	--direction.y;
	//}
	//// 좌 이동
	//if (mouseScreenPos.x <= 50.f)
	//{
	//	--direction.x;
	//}
	//// 우 이동
	//if (mouseScreenPos.x >=  m_screenSize.x-50.f)
	//{
	//	++direction.x;
	//}

	//direction.Normalize();

	//Vector2 distance = direction * m_moveSpeed * _deltaTime;

	//m_camera->MoveCamera(distance);

	/// 카메라 확대 

	//if(m_inputManager->IsKeyState(KEY::F1, KEY_STATE::TAP))
	//{
	//	m_camera->ZoomCamera(Vector2(0.1f, 0.1f));
	//}
	//if (m_inputManager->IsKeyState(KEY::F2, KEY_STATE::TAP))
	//{
	//	m_camera->ZoomCamera(Vector2(-0.1f, -0.1f));
	//}

}

Vector2 CameraManager::ScreenToWorld(const Vector2& _screen) const
{
	Vector2 camera = m_camera->ScreenToCamera(_screen);
	return m_camera->CameraToWorld(camera);
}

Vector2 CameraManager::ScreenToCamera(const Vector2& _screen) const
{
	return m_camera->ScreenToCamera(_screen);
}

Vector2 CameraManager::WorldToCamera(const Vector2& _world) const
{
	return m_camera->WorldToCamera(_world);
}

Vector2 CameraManager::WorldToScreen(const Vector2& _world) const
{
	Vector2 camera = m_camera->WorldToCamera(_world);

	return m_camera->CameraToScreen(camera);
}

Vector2 CameraManager::CameraToScreen(const Vector2& _camera) const
{
	return m_camera->CameraToScreen(_camera);
}

Vector2 CameraManager::CameraToWorld(const Vector2& _camera) const
{
	return m_camera->CameraToWorld(_camera);
}

void CameraManager::ResetCamera() const
{
	m_camera->ResetCamera(m_screenSize);
}
