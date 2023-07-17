#pragma once
#include "Component.h"

class Transform;

/// <summary>
/// �ؽ�ó�� �������ϴ� ������Ʈ�̴� 
/// 
/// �ؽ�ó �������� Ű�������� �ڼ��� ������ 
/// �������� ����ִ� �����̴�.
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
    /// �������ϴ� �ؽ�Ʈ �̹��� Key��
    wstring m_textKey;

    // ������Ʈ���� ������
    Vector2 m_offset;

    // ���� 
    float m_alpha;

    Transform* m_transform;
};

