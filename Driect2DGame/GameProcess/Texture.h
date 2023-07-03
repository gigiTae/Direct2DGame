#pragma once
#include "Resource.h"
class Texture :
    public Resource
{
public:
    Texture();
    ~Texture();

public:
    void SetBitmap(ID2D1Bitmap* _bitmap) { m_bitmap = _bitmap; }
    const ID2D1Bitmap* GetBitmap() { return m_bitmap; }

private:
    ID2D1Bitmap* m_bitmap;
};

