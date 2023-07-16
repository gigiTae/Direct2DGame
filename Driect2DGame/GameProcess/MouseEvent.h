#pragma once
#include "Component.h"

/// <summary>
/// UI���� ������Ʈ 
/// ���콺 �Է¿� ���� �Լ� ȣ���� ����Ѵ�.
/// 
/// </summary>
class MouseEvent :
    public Component
{
public:
    MouseEvent();
    ~MouseEvent();

    void LateUpdate(float _deltaTime) override;

public:
    bool IsMouseOn() { return m_mouseOn; }
    bool IsLBtnDown() { return m_LBtnDown; }

    void Render(D2DRenderer* _d2DRenderer) override;

    void SetMouseOn(bool _isMouseOn) { m_mouseOn = _isMouseOn; }
    void SetLBtnDown(bool _isLBtnDown) { m_LBtnDown = _isLBtnDown; }
private:
    bool m_mouseOn; // UI ���� ���콺�� �ִ���
    bool m_LBtnDown; // UI�� ���� ���콺 ��ư�� �������� �ִ���

};

