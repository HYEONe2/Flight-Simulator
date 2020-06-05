#include "TimerClass.h"

TimerClass::TimerClass()
{
}

TimerClass::TimerClass(const TimerClass& other)
{
}

TimerClass::~TimerClass()
{
}

bool TimerClass::Initialize()
{
	// Check to see if this system supports high performance timers.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_iFrequency);
	if (m_iFrequency == 0)
	{
		return false;
	}
	// Find out how many times the frequency counter ticks every millisecond.
	m_fTicksPerMs = (float)(m_iFrequency / 1000);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_iStartTime);
	return true;
}

void TimerClass::Frame()
{
	INT64 currentTime;
	float timeDifference;
	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);
	timeDifference = (float)(currentTime - m_iStartTime);
	m_fFrameTime = timeDifference / m_fTicksPerMs;
	m_iStartTime = currentTime;
	return;
}

float TimerClass::GetTime()
{
	return m_fFrameTime;
}