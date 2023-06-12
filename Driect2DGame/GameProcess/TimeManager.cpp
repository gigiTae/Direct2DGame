#include "GameProcessPCH.h"
#include "TimeManager.h"

TimeManager::TimeManager()
	:m_curentCount{}
	,m_frequency{}
	,m_prevCount{}
	,m_deltaTime(0.)
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Initalize()
{
	QueryPerformanceFrequency(&m_frequency); // 프로세서의 카운터 값의 빈도
	QueryPerformanceCounter(&m_prevCount); // 이전 프레임의 카운터 값
}

double TimeManager::Update()
{
	QueryPerformanceCounter(&m_curentCount);
	m_deltaTime = (m_curentCount.QuadPart - m_prevCount.QuadPart) / (double)m_frequency.QuadPart;

	m_prevCount.QuadPart = m_curentCount.QuadPart;

	return m_deltaTime;
}

void TimeManager::Finalize()
{
}
