#pragma once
#include "Component.h"

class Animation;

/// <summary>
/// �ִϸ��̼� ����� ����ϴ� ������Ʈ�̴�
/// �ִϸ����ʹ� ���������� �ִϸ��̼��� ������ �ִ� �����̴�
///
/// 
/// �̸� ������ �ִϸ��̼� ������ �д� �ʿ��غ��� -> ��Ȱ�밡�ɼ� ����
/// 
/// 20203.07.04 ���� 10�� 
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

    // �ִϸ��̼� ã��
    Animation* FindAnimation(const wstring& _name);

    // �ִϸ��̼� ���
    void Play(const wstring& _name, bool _repeat);

    void LateUpdate(float _deltaTime) override;
    void Render(D2DRenderer* _d2DRenderer) override;

private:
    map<wstring, Animation*> m_animations; // ��� animation ����
    Animation* m_currentAnimation; // ���� ������� �ִϸ��̼�
    bool m_repeat; // �ݺ��������
};

