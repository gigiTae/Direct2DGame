#pragma once
#include "MonoBehaviour.h"

/// <summary>
/// ������ �ν��ϴ� �������� �����ϴ� ������Ʈ�̴�.
/// 
/// 2023.7.13 19:58 gitae 
/// </summary>
class UnitSensor :
    public MonoBehaviour
{
public:
    UnitSensor();
    ~UnitSensor();

    bool IsSeneseUnit(GameObject* _target);

    void Update(float _deltaTime) override;

    // �νĹ������� ������Ʈ���� �����Ѵ�.
    void OnCollisionEnter(const Collision& _collision) override;
    
    // �νĹ��� ������ ���� ������Ʈ�� ����Ʈ���� ������.
    void OnCollisionExit(const Collision& _collision) override;

private:
    map<string, GameObject*> m_senseObjects; // �����ϰ� �ִ� ������Ʈ ����Ʈ�̴�.
    GameObject* m_target; //���� �������� �����̴�.
};

