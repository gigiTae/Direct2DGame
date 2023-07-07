#pragma once

/// <summary>
/// ī�޶� ����ϴ� �Ŵ���
/// 
/// 2023.7.7 23:04 gitae
/// </summary>
class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	void Initalize(D2DRenderer* _renderer, Vector2 _screenSize);

	/// ��ũ�� ��ǥ�迡�� ���� ��ǥ��� ��ȯ���ش�.
	Vector2 ScreenToWorld(const Vector2& _screen) const;

private:
	D2DCamera* m_camera;
	D2DRenderer* m_d2DRenderer;
	Vector2 m_screenSize;
};

