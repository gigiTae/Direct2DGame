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
    void Shoot(GameObject* _target, float _speed);

private:
    Vector2 m_direct; // 이동방향
    Vector2 m_desitinaiton; // 최종도착지
    
    GameObject* m_target; // 타겟

    float m_prevDistance; // 이전 위치 차이
    float m_shootSpeed;
};

