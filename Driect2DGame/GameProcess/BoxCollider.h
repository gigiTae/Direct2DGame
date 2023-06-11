#pragma once

class GameObject;
/// <summary>
/// 박스형 콜라이더이다
/// m_rotation 값에 따라서 
/// OBB, AABB 충돌을 할지 정한다.
/// </summary>
class BoxCollider
{
public:
	BoxCollider();
	~BoxCollider();

	void SetOwner(GameObject* _owner) { m_owner = _owner; }
	void SetPos(Vector2 _pos) { m_position = _pos; }
	void SetOffset(Vector2 _offset) { m_offset = _offset; }
	void SetScale(Vector2 _scale) { m_scale = _scale; }
	void SetRotation(float _rotation) { m_rotation = _rotation; }

	GameObject* GetOwner() { return m_owner; }
	Vector2 GetPos() { return m_position; }
	Vector2 GetOffset() { return m_offset; }
	Vector2 GetScale() { return m_scale; }
	// 회전각도를 반환
	float GetRotation() { return m_rotation; }
	
	// 회전가능한 박스인지 아닌지
	bool IsRotatable() { return m_isRotate; }

	void DebugRender(D2DRenderer* _d2DRenderer);
private:
	// 콜라이더를 소유한 오브젝트
	GameObject* m_owner;

	Vector2 m_position;
	Vector2 m_offset;
	Vector2 m_scale;

	// 회전가능한 박스인지 여부를 체크해서 AABB,OBB등의 처리를 해준다
	bool m_isRotate;
	// 회전각도
	float m_rotation;

	// 콜라이더 활성화 여부
	bool m_active;

};

