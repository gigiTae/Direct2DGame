#pragma once
#include "Component.h"

class Transform;

/// <summary>
/// 텍스처를 랜더링하는 컴포넌트이다 
/// 
/// 텍스처 랜더링은 키값만으로 자세한 정보는 
/// 랜더러가 들고있는 형태이다.
/// </summary>
class TextureRenderer :
    public Component
{
public:
    TextureRenderer();
    ~TextureRenderer();

    void Render(D2DRenderer* _d2DRenderer) override;
    void Start() override;

    void SetKey(const wstring& _key) { m_textKey = _key; }
    void SetOffset(const Vector2& _offset) { m_offset = _offset; }

    const wstring GetKey() { return m_textKey; }
    const Vector2& GetOffset() { return m_offset; }

    void SetAlpha(float _alpha) { m_alpha = FMath::Clamp(_alpha, 0.f, 1.f); }
    float GetAlpha() { return m_alpha; }

private:
    /// 랜더링하는 텍스트 이미지 Key값
    wstring m_textKey;

    // 오브젝트와의 오프셋
    Vector2 m_offset;

    // 투명도 
    float m_alpha;

    Transform* m_transform;
};

