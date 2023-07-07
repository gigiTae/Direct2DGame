#pragma once
#include "Component.h"

/// <summary>
/// UI관련 컴포넌트 
/// 마우스 입력에 관한 함수 호출을 담당한다.
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
    bool m_mouseOn; // UI 위에 마우스가 있는지
    bool m_lBtnDown; // UI에 왼쪽 마우스 버튼이 눌린적이 있는지

};

