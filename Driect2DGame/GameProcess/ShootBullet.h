#pragma once
#include "MonoBehaviour.h"

/// <summary>
/// 발사용 컴포넌트
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
    Vector2 m_direct; // 이동방향
    float m_shootSpeed;
};

