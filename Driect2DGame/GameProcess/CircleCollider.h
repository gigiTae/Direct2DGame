#pragma once

#include "Collider.h"

class GameObject;
class InputManager;
/// <summary>
/// ���� �ݶ��̴� 
/// 
/// </summary>
class CircleCollider :public Collider
{
public:
	CircleCollider();
	~CircleCollider();

public:
	/// �̺�Ʈ ����
	void LateUpdate(float _deltaTime) override;
	void DebugRender(D2DRenderer* _d2DRenderer) override;

public:
	void SetActive(bool _isAtive) { m_active = _isAtive; }
	void SetPosition(Vector2 _position) { m_position = _position; }
	void SetOffset(Vector2 _offset) { m_offset = _offset; }
	void SetRadius(float _raidus) { m_radius = _raidus; }

	bool IsActive() { return m_active; }
	Vector2 GetOffset() { return m_offset; }
	Vector2 GetPosition() { return m_position; }
	float GetRadius() { return m_radius; }

public:
	bool Collides(Vector2 _position) override;
	bool Collides(CircleCollider* _circle) override;
	bool Collides(BoxCollider* _box) override;

public:
	Vector2 GetMinPoint() const override;
	Vector2 GetMaxPoint() const override;

private:
	Vector2 m_offset;
	Vector2 m_position; 

	float m_radius;

	// �ݶ��̴� Ȱ��ȭ ����
	bool m_active;
};

