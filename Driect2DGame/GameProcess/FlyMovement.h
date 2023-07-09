#pragma once
#include "UnitMovement.h"
class FlyMovement :
    public UnitMovement
{
public:
    FlyMovement();
    ~FlyMovement();

public:
    void Move(float _deltaTime) override;
};

