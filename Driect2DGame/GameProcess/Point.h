#pragma once
#include "GameObject.h"
class Point :
    public GameObject
{
public:
	Point();
	~Point();

	void Initalize() override;
	void Update(float _deltaTime, InputManager* inputManager) override;
};

