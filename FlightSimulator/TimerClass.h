#pragma once

#include <windows.h>

class TimerClass
{
public:
	TimerClass();
	TimerClass(const TimerClass&);
	~TimerClass();

	bool Initialize();
	void Frame();

	float GetTime();

private:
	INT64 m_iFrequency;
	float m_fTicksPerMs;
	INT64 m_iStartTime;
	float m_fFrameTime;
};
