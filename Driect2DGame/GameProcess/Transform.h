#pragma once

#include "Component.h"

/// <summary>
/// 위치,크기를 관리하는 컴포넌트이다
/// 
/// 
/// </summary>
class Transform : public Component
{
public:
	Transform();
	~Transform();
public:
	void SetPosition(Vector2 _position) { m_position = _position; }
	void SetRotation(float _rotation) { m_rotation = _rotation; }
	void SetScale(Vector2 _scale) { m_scale = _scale; }

	void AddRotation(float _radian);
	void AddPosition(Vector2 _addPosition) { m_position += _addPosition; }

	Vector2 GetPosition() { return m_position; }
	Vector2 GetScale() { return m_scale; }
	float GetRotation() { return m_rotation; }

	void Update();
	void DebugRender(D2DRenderer* _d2DRenderer);
private: 
	Vector2 m_position;
	float m_rotation;
	Vector2 m_scale;
};

