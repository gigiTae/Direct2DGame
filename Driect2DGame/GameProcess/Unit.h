#pragma once
#include "MonoBehaviour.h"

enum class UNIT_STATE
{
    HOLD, // ���� ����
    ATTACK, // ���� ����
    MOVE, // �̵����� 
    

};

class UnitMovement;

/// <summary>
/// �⺻������ ��Ÿũ����Ʈ ������ ������ ������Ʈ�̴�
/// 
/// </summary>
class Unit :
    public MonoBehaviour
{
public:
    Unit();
    ~Unit();

    void PreRender(D2DRenderer* _d2DRenderer) override;
    void SetSelct(bool _isSelect) { m_isSelect = _isSelect; }
    void Update(float _deltaTime) override;

private:
    bool m_isSelect; // �δ������� �������� lllollllllol;;
    UNIT_STATE m_state;

    UnitMovement* m_movement; // ������ �������� ����ϴ� ������Ʈ 
};

