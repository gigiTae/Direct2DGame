#pragma once
#include "Component.h"

class Animation;

/// <summary>
/// 애니메이션 출력을 담당하는 컴포넌트이다
/// 애니메이터는 여러가지의 애니메이션을 가질수 있는 구조이다
///
/// 
/// 미리 생성한 애니메이션 파일을 읽는 필요해보임 -> 재활용가능성 증가
/// 
/// 20203.07.04 오후 10시 
/// </summary>
class Animator :
    public Component
{
public:
    Animator();
    ~Animator();

public:
    void CreateAnimation(const wstring& _name, const wstring& _textureKey
    , Vector2 _startLeftTop, Vector2 _sliceSize, Vector2 _step
    , float _duration, UINT _frameCount);

    // 애니메이션 찾기
    Animation* FindAnimation(const wstring& _name);

    // 애니메이션 재생
    void Play(const wstring& _name, bool _repeat);

    void LateUpdate(float _deltaTime) override;
    void Render(D2DRenderer* _d2DRenderer) override;

private:
    map<wstring, Animation*> m_animations; // 모든 animation 정보
    Animation* m_currentAnimation; // 현재 재생중인 애니메이션
    bool m_repeat; // 반복재생여부
};

