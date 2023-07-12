#pragma once
#include "MonoBehaviour.h"

enum class UNIT_STATE
{
    HOLD, // 정지 상태
    ATTACK, // 공격 상태
    MOVE, // 이동상태 
    DEAD, // 죽음 
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

    void Initalize(UnitMovement* _movement);
    void Finalize() override;

	void PreRender(D2DRenderer* _d2DRenderer) override;
	void SetSelct(bool _isSelect) { m_isSelect = _isSelect; }
    void Update(float _deltaTime) override;

    /// 유닛에게 이동명령을 지시하는 함수
    void MoveUnit(Vector2 _destination);
    
    /// 유닛에게 고정명령을 지시하는 함수
    void HoldUnit();

public:
    void OnCollisionStay(const Collision& _collision) override;

private:
    bool m_isSelect; // 부대지정된 유닛인지 
    UNIT_STATE m_state;

    GameObject* m_target; // 현재 공격중인 오브젝트

    float m_hp; // 유닛 체력

    UnitMovement* m_movement; // 유닛의 움직임을 담당하는 컴포넌트 
};

