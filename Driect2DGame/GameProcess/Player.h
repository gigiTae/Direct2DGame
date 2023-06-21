#pragma once
#include "GameObject.h"
class Player :
    public GameObject
{
public:
    Player(const wstring& _name);
    ~Player();

    void Initalize() override;
    void Update(float _deltaTime, InputManager* _inputManager) override;
    void FixedUpdate(float _fixedDeltaTime, InputManager* _inputManager) override;
    void Finalize() override;

    void SetSpeed(float _speed) { m_moveSpeed = _speed; }
    float GetSpeed() { return m_moveSpeed; }
private:
    float m_moveSpeed;
};

