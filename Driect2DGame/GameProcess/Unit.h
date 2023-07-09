#pragma once
#include "MonoBehaviour.h"

enum class UNIT_STATE
{
    HOLD, // 정지 상태
    ATTACK, // 공격 상태
    MOVE, // 이동상태 
    

};

class UnitMovement;

/// <summary>
/// 기본적으로 스타크래프트 유닛이 가지는 컴포넌트이다
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
    bool m_isSelect; // 부대지정된 유닛인지 lllollllllol;;
    UNIT_STATE m_state;

    UnitMovement* m_movement; // 유닛의 움직임을 담당하는 컴포넌트 
};

