#pragma once

class GameObject;
/// <summary>
/// 리지드 바디 컴포넌트
/// 오브젝의 물리에 관한 처리를 함
/// 물리 엔진을 만들기 위한 기초 컴포넌트
/// </summary>
class RigidBody
{
	
private: // 멤버변수 공간
	GameObject* m_owner;
	
	Vector2 m_force; // 방향

};

