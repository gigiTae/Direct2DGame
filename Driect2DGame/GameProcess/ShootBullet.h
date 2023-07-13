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
    void Shoot(Vector2 _dircet, float _speed);

private:
    Vector2 m_direct; // �̵�����
    float m_shootSpeed;
};

