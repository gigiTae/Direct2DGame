#pragma once
#include "MonoBehaviour.h"
class BoxRenderer :
    public MonoBehaviour
{
public:
    BoxRenderer();
    ~BoxRenderer();

    void Render(D2DRenderer* _d2DRenderer) override;

private:
};

