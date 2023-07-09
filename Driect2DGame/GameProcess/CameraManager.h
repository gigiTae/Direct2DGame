#pragma once

class InputManager;
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

	void Initalize(D2DRenderer* _renderer, Vector2 _screenSize, InputManager* _inputManager);
	void Update(float _deltaTime);

	/// ��ũ�� ��ǥ�迡�� ���� ��ǥ��� ��ȯ���ش�.
	Vector2 ScreenToWorld(const Vector2& _screen) const;

	// ��ũ�� ��ǥ�迡�� ī�޶� ��ǥ��� ��ȯ
	Vector2 ScreenToCamera(const Vector2& _screen) const;
	
	// ������ǥ���� ī�޶� ��ǥ��� ��ȯ
	Vector2 WorldToCamera(const Vector2& _world) const;
	
	// ���� ��ǥ���� ��ũ�� ��ǥ��� ��ȯ 
	Vector2 WorldToScreen(const Vector2& _world) const;
	
	// ī�޶� ��ǥ�迡�� ��ũ�� ��ǥ�� ��ȯ
	Vector2 CameraToScreen(const Vector2& _camera) const;
	
	// ī�޶� ��ǥ�迡�� ���� ��ǥ�� ��ȯ 
	Vector2 CameraToWorld(const Vector2& _camera) const;
	
private:
	D2DCamera* m_camera;
	D2DRenderer* m_d2DRenderer;
	Vector2 m_screenSize;
	InputManager* m_inputManager;
	
	/// ī�޶� �̵��ӵ�
	float m_moveSpeed;
};

