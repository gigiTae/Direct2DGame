#pragma once
#include "GameObject.h"
class Line :
    public GameObject
{
public:
    Line();
    ~Line();

    void Initalize() override;
    void Update(float _deltaTime, InputManager* inputManager) override;
};

