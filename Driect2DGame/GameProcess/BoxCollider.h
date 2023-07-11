#pragma once

#include "Collider.h"
class GameObject;
class InputManager;
struct Collision;
/// <summary>
/// 박스형 콜라이더이다
/// m_rotation 값에 따라서 
/// OBB, AABB 충돌을 할지 정한다.
/// </summary>
class BoxCollider :public Collider
{
public:
	BoxCollider();
	~BoxCollider();

	void LateUpdate(float _deltaTime) override;

	void SetActive(bool _isAtive) { m_active = _isAtive; }
	void SetPosition(Vector2 _pos) { m_position = _pos; }
	void SetOffset(Vector2 _offset) { m_offset = _offset; }
	void SetScale(Vector2 _scale) { m_scale = _scale; }
	void SetRotation(float _rotation) { m_rotation = _rotation; }
	void SetRotatble(bool _isRoatatble) { m_isRotatable = _isRoatatble; }

	bool IsActive() { return m_active; }
	Vector2 GetPosition() { return m_position; }
	Vector2 GetOffset() { return m_offset; }
	Vector2 GetScale() { return m_scale; }

	// 회전각도를 반환
	float GetRotation() const { return m_rotation; }
	// 회전가능한 박스인지 아닌지
	bool IsRotatable() const { return m_isRotatable; }

	void DebugRender(D2DRenderer* _d2DRenderer);

public:
	bool Collides(Vector2 _position) override;
	bool Collides(CircleCollider* _circle) override;
	bool Collides(BoxCollider* _box) override;

public:
	Vector2 GetMinPoint()const override;
	Vector2 GetMaxPoint()const override;

private:
	Vector2 m_position;
	Vector2 m_offset;
	Vector2 m_scale;

	// 회전가능한 박스인지 여부를 체크해서 AABB,OBB등의 처리를 해준다
	bool m_isRotatable;
	// 회전각도 라디안
	float m_rotation;
	// 콜라이더 활성화 여부
	bool m_active;
};

