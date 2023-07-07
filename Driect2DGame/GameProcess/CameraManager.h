#pragma once

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

	void Initalize(D2DRenderer* _renderer, Vector2 _screenSize);

	/// 스크린 좌표계에서 월드 좌표계로 변환해준다.
	Vector2 ScreenToWorld(const Vector2& _screen) const;

private:
	D2DCamera* m_camera;
	D2DRenderer* m_d2DRenderer;
	Vector2 m_screenSize;
};

