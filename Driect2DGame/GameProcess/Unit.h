#pragma once
#include "MonoBehaviour.h"


class UnitMovement;
class UnitSensor;
class UnitAttack;

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

    void Start() override;
    void Finalize() override;

    void Initalize(UnitInfomaiton _info);

	void PreRender(D2DRenderer* _d2DRenderer) override;
	void SetSelct(bool _isSelect) { m_isSelect = _isSelect; }
    void Update(float _deltaTime) override;
    
    // 유닛에게 공격명령 지시
    void AttackUnit(GameObject* _unit);
    // 유닛에게 이동명령을 지시
    void MoveUnit(Vector2 _destination);
    // 유닛에게 고정명령을 지시
    void HoldUnit();

    const UnitInfomaiton& GetUnitInfomation() { return m_infomation; }


private:
    bool m_isSelect; // 부대지정된 유닛인지 
    GameObject* m_target; //  현재 타겟팅중인 오브젝트

    UnitAttack* m_attack; // 유닛의 공격을 담당한다.
    UnitInfomaiton m_infomation; // 유닛 정보
    UnitSensor* m_unitSensor; // 유닛의 인식정보들을 담당한다.
    UnitMovement* m_movement; // 유닛의 움직임을 담당하는 컴포넌트 
};

