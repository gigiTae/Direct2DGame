#pragma once
#include "MonoBehaviour.h"
class Movement :
    public MonoBehaviour
{
public:
    Movement();
    ~Movement();

    void Update(float _deltaTime, InputManager* _inputManager) override;

private:
    float m_speed; // �ӵ�

};
