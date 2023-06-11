#pragma once

class GameObject;
/// <summary>
/// �ڽ��� �ݶ��̴��̴�
/// m_rotation ���� ���� 
/// OBB, AABB �浹�� ���� ���Ѵ�.
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
	// ȸ�������� ��ȯ
	float GetRotation() { return m_rotation; }
	
	// ȸ�������� �ڽ����� �ƴ���
	bool IsRotatable() { return m_isRotate; }

	void DebugRender(D2DRenderer* _d2DRenderer);
private:
	// �ݶ��̴��� ������ ������Ʈ
	GameObject* m_owner;

	Vector2 m_position;
	Vector2 m_offset;
	Vector2 m_scale;

	// ȸ�������� �ڽ����� ���θ� üũ�ؼ� AABB,OBB���� ó���� ���ش�
	bool m_isRotate;
	// ȸ������
	float m_rotation;

	// �ݶ��̴� Ȱ��ȭ ����
	bool m_active;

};

