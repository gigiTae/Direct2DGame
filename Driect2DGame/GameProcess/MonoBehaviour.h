#pragma once
#include "Component.h"

class InputManager;

struct Collision;

/// <summary>
/// UserScript의 추상클래스이다
///
/// </summary>
class MonoBehaviour abstract :
    public Component
{
public:
    MonoBehaviour() = default;
    ~MonoBehaviour() override;

    /// 생성 관련 함수
    virtual void Initalize() {};
    virtual void Finalize() {};

    /// 이벤트 관련함수
    virtual void Update(float _deltaTime, InputManager* _inputManager) {};
    virtual void FixedUpdate(float _fixedDeltaTime, InputManager* _inputManager) {};
    virtual void PreRender(D2DRenderer* _d2DRenderer) {};
    virtual void Render(D2DRenderer* _d2DRenderer) {};
    virtual void PostRender(D2DRenderer* _d2DRenderer) {};

    /// 충돌 관련 함수
	virtual void OnCollisionStay(const Collision& _collision, const InputManager* _inputManager) {};
	virtual void OnCollisionEnter(const Collision& _collision, const InputManager* _inputManager) {};
	virtual void OnCollisionExit(const Collision& _collision, const InputManager* _inputManager) {};

    /// 마우스 입력 함수
    virtual void OnMouse() {};
    virtual void OnMouseUp() {};
    virtual void OnMouseDown() {};
    virtual void OnMouseClicked() {};
};

