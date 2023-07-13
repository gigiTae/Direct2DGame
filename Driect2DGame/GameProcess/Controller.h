#pragma once
#include "MonoBehaviour.h"

/// <summary>
/// �δ������� �����ϴ� UI 
/// BackUI�� ���ϰ� ���� ������Ʈ���� �̵�, ���ݵ��� 
/// �δ��������� �����ִ� ������Ʈ�̴�.
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
    bool m_isDragging; // �巡�� ������

    Vector2 m_dragStart; 
    Vector2 m_dragEnd;

    /// ������ �δ븦 ������ ������ �迭
    vector<GameObject*> m_selectUnits;

    /// ������ �簢������ �ִ� ������Ʈ�� �ҷ�����
    void GetUnits();
};

