#pragma once

class GameObject;
/// <summary>
/// ������ �ٵ� ������Ʈ
/// �������� ������ ���� ó���� ��
/// ���� ������ ����� ���� ���� ������Ʈ
/// </summary>
class RigidBody
{
	
private: // ������� ����
	GameObject* m_owner;
	
	Vector2 m_force; // ����

};

