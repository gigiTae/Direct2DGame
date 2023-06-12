#pragma once
#include "GameObject.h"
class Box :
    public GameObject
{
public:
	Box();
	~Box();
	void Initalize() override;
	void Update(float _deltaTime, InputManager* inputManager) override;
	void Finalize() override;

};

