#pragma once
#include "MonoBehaviour.h"

/// <summary>
/// 부대지정을 지원하는 UI 
/// BackUI에 속하고 게임 오브젝트들을 이동, 공격등을 
/// 부대지정으로 도와주는 컴포넌트이다.
/// </summary>
class Controller :
    public MonoBehaviour
{
public:
    Controller();
    ~Controller();

    void Render(D2DRenderer* _d2DRenderer) override;

    void Update(float _deltaTime) override;

    void OnMouseDown() override;
    void OnMouse() override;
    void OnMouseUp() override;
    
private:
    bool m_isDragging; // 드래그 중인지

    Vector2 m_dragStart; 
    Vector2 m_dragEnd;

    /// 지정한 부대를 정보를 가지는 배열
    vector<GameObject*> m_selectUnits;

    /// 지정된 사각형내에 있는 오브젝트들 불러오기
    void GetUnits();
};

