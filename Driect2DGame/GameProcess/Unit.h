#pragma once
#include "MonoBehaviour.h"

enum class UNIT_STATE
{
    HOLD, // ���� ����
    ATTACK, // ���� ����
    MOVE, // �̵����� 
    DEAD, // ���� 
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

    void Initalize(UnitMovement* _movement);
    void Finalize() override;

	void PreRender(D2DRenderer* _d2DRenderer) override;
	void SetSelct(bool _isSelect) { m_isSelect = _isSelect; }
    void Update(float _deltaTime) override;

    /// ���ֿ��� �̵������ �����ϴ� �Լ�
    void MoveUnit(Vector2 _destination);
    
    /// ���ֿ��� ��������� �����ϴ� �Լ�
    void HoldUnit();

public:
    void OnCollisionStay(const Collision& _collision) override;

private:
    bool m_isSelect; // �δ������� �������� 
    UNIT_STATE m_state;

    GameObject* m_target; // ���� �������� ������Ʈ

    float m_hp; // ���� ü��

    UnitMovement* m_movement; // ������ �������� ����ϴ� ������Ʈ 
};

