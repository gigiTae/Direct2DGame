#pragma once
#include "Component.h"

class InputManager;

struct Collision;

/// <summary>
/// UserScript�� �߻�Ŭ�����̴�
///
/// </summary>
class MonoBehaviour abstract :
    public Component
{
public:
    MonoBehaviour(string _name);
    ~MonoBehaviour() override;

    /// ���� ���� �Լ�
    virtual void Initalize() {};
    virtual void Finalize() {};

    /// �̺�Ʈ �����Լ�
    void Update(float _deltaTime) override {};
    void FixedUpdate(float _fixedDeltaTime) override {};
    void PreRender(D2DRenderer* _d2DRenderer) override {};
    void Render(D2DRenderer* _d2DRenderer) override {};
    void PostRender(D2DRenderer* _d2DRenderer) override {};

    /// �浹 ���� �Լ�
	virtual void OnCollisionStay(const Collision& _collision) {};
	virtual void OnCollisionEnter(const Collision& _collision) {};
	virtual void OnCollisionExit(const Collision& _collision) {};

    /// ���콺 �Է� �Լ�
    virtual void OnMouse() {};
    virtual void OnMouseUp() {};
    virtual void OnMouseDown() {};
    virtual void OnMouseClicked() {};
};

