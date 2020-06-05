#include "FpsClass.h"

FpsClass::FpsClass()
{
}

FpsClass::FpsClass(const FpsClass& other)
{
}

FpsClass::~FpsClass()
{
}

//The Initialize function sets all the counters to zero and starts the timer.
void FpsClass::Initialize()
{
	m_iFps = 0;
	m_iCount = 0;
	m_lStartTime = timeGetTime();
	return;
}

void FpsClass::Frame()
{
	m_iCount++;
	if (timeGetTime() >= (m_lStartTime + 1000))
	{
		m_iFps = m_iCount;
		m_iCount = 0;
		m_lStartTime = timeGetTime();
	}
}

int FpsClass::GetFps()
{
	return m_iFps;
}