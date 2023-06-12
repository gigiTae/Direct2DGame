#pragma once

struct Collision;
class InputManager;

// �ݶ��̴� �������̽� 
class Collider abstract
{
public:
	virtual void FinalUpdate() abstract;
	virtual void DebugRender(D2DRenderer* _d2DRenderer) abstract;

public:
	virtual void OnCollisionEnter(const Collision& _collision,const InputManager* _inputManager) abstract;
	virtual void OnCollisionExit(const Collision& _collision, const InputManager* _inputManager) abstract;
	virtual void OnCollisionStay(const Collision& _collision, const InputManager* _inputManager) abstract;
};