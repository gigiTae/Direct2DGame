#pragma once
#include "GameObject.h"
class Player :
    public GameObject
{
public:
    Player() = default;
    ~Player();

    void Initalize() override;
    void Update(float _deltaTime, InputManager* inputManager) override;
    void Finalize() override;

    void SetSpeed(float _speed) { m_moveSpeed = _speed; }
    float GetSpeed() { return m_moveSpeed; }
private:
    float m_moveSpeed;
};

