#pragma once
#include "MonoBehaviour.h"

/// <summary>
/// 유닛이 인식하는 정보들을 관리하는 컴포넌트이다.
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

    // 인식범위내의 오브젝트들을 저장한다.
    void OnTriggerEnter(const Collision& _collision) override;
    
    // 인식범위 밖으로 나간 오브젝트를 리스트에서 꺼낸다
    void OnTriggerExit(const Collision& _collision) override;

private:
    map<string, GameObject*> m_senseObjects; // 감지하고 있는 오브젝트 리스트이다.
    GameObject* m_target; //현재 공격중인 유닛이다.
};

