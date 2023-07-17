#pragma once
#include "MonoBehaviour.h"


class UnitMovement;
class UnitSensor;
class UnitAttack;
class BarUI;

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

    void Start() override;
    void Finalize() override;

    void Initalize(UnitInfomaiton _info);

	void PreRender(D2DRenderer* _d2DRenderer) override;
	void SetSelct(bool _isSelect) { m_isSelect = _isSelect; }
    void Update(float _deltaTime) override;
    
    // ���ֿ��� ���ݸ�� ����
    void AttackUnit(GameObject* _unit);
    // ���ֿ��� �̵������ ����
    void MoveUnit(Vector2 _destination);
    // ���ֿ��� ��������� ����
    void HoldUnit();
    
    // ������ ������ ȣ���ϴ� �Լ�
    void TakeDamage(float _damage);

    const UnitInfomaiton& GetUnitInfomation() { return m_infomation; }

private:
    // ���� ������Ʈ ���� 
    void UpdateHpBar();

private:
    bool m_isSelect; // �δ������� �������� 
    GameObject* m_target; //  ���� Ÿ�������� ������Ʈ

    BarUI* m_hpBar; // hpBar
    UnitAttack* m_attack; // ������ ������ ����Ѵ�.
    UnitInfomaiton m_infomation; // ���� ����
    UnitSensor* m_unitSensor; // ������ �ν��������� ����Ѵ�.
    UnitMovement* m_movement; // ������ �������� ����ϴ� ������Ʈ 
};

