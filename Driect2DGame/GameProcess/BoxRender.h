#pragma once
#include "MonoBehaviour.h"
class BoxRender :
    public MonoBehaviour
{
public:
    BoxRender();
    ~BoxRender();

    void Render(D2DRenderer* _d2DRenderer) override;
};

