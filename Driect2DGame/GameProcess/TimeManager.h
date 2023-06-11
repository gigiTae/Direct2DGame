#pragma once

// deltaTime을 계산해주는 클래스
class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	void Initalize();
	
	// deltaTime을 반환해준다
	double Update();
	void Finalize();

private:
	LARGE_INTEGER m_curentCount;
	LARGE_INTEGER m_prevCount;
	LARGE_INTEGER m_frequency;

	double m_deltaTime;
};

