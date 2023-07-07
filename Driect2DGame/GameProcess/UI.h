#pragma once
#include "Component.h"

/// <summary>
/// UI���� ������Ʈ 
/// ���콺 �Է¿� ���� �Լ� ȣ���� ����Ѵ�.
/// 
/// </summary>
class UI :
    public Component
{
public:
    UI();
    ~UI();

    void Render(D2DRenderer* _d2DRenderer);
    void LateUpdate(float _deltaTime) override;

private:
    bool m_mouseOn; // UI ���� ���콺�� �ִ���
    bool m_lBtnDown; // UI�� ���� ���콺 ��ư�� �������� �ִ���

};

