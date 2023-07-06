#pragma once
#include "Manager.h"

// deltaTime�� ������ִ� Ŭ����
class TimeManager : public Manager
{
public:
	TimeManager();
	~TimeManager();

	void Initalize(const Vector2& _screenSize);

	// deltaTime�� ��ȯ���ش�
	double Update();
	void DebugRender(D2DRenderer* _d2dRenderer);
	void Finalize();

private:
	LARGE_INTEGER m_curentCount;
	LARGE_INTEGER m_prevCount;
	LARGE_INTEGER m_frequency;

	Vector2 m_screenSize;

	double m_deltaTime;
	double m_elapsedTime;
	int m_updateCount;
	int m_fps;
};

