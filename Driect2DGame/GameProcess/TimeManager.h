#pragma once

// deltaTime�� ������ִ� Ŭ����
class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	void Initalize();
	
	// deltaTime�� ��ȯ���ش�
	double Update();
	void Finalize();

private:
	LARGE_INTEGER m_curentCount;
	LARGE_INTEGER m_prevCount;
	LARGE_INTEGER m_frequency;

	double m_deltaTime;
};

