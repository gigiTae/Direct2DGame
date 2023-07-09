#pragma once

class InputManager;
/// <summary>
/// 카메라를 담당하는 매니져
/// 
/// 2023.7.7 23:04 gitae
/// </summary>
class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	void Initalize(D2DRenderer* _renderer, Vector2 _screenSize, InputManager* _inputManager);
	void Update(float _deltaTime);

	/// 스크린 좌표계에서 월드 좌표계로 변환해준다.
	Vector2 ScreenToWorld(const Vector2& _screen) const;

	// 스크린 좌표계에서 카메라 좌표계로 변환
	Vector2 ScreenToCamera(const Vector2& _screen) const;
	
	// 월드좌표에서 카메라 좌표계로 변환
	Vector2 WorldToCamera(const Vector2& _world) const;
	
	// 월드 좌표에서 스크린 좌표계로 변환 
	Vector2 WorldToScreen(const Vector2& _world) const;
	
	// 카메라 좌표계에서 스크린 좌표계 변환
	Vector2 CameraToScreen(const Vector2& _camera) const;
	
	// 카메라 좌표계에서 월드 좌표계 변환 
	Vector2 CameraToWorld(const Vector2& _camera) const;
	
private:
	D2DCamera* m_camera;
	D2DRenderer* m_d2DRenderer;
	Vector2 m_screenSize;
	InputManager* m_inputManager;
	
	/// 카메라 이동속도
	float m_moveSpeed;
};

