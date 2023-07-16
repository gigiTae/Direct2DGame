#pragma once
#include "MonoBehaviour.h"

/// <summary>
/// �߻�� ������Ʈ
/// </summary>
class ShootBullet :
    public MonoBehaviour
{
public:
    ShootBullet();
    ~ShootBullet();

    void Update(float _deltaTime) override;
    void Shoot(GameObject* _target, float _speed);

private:
    Vector2 m_direct; // �̵�����
    Vector2 m_desitinaiton; // ����������
    
    GameObject* m_target; // Ÿ��

    float m_prevDistance; // ���� ��ġ ����
    float m_shootSpeed;
};

