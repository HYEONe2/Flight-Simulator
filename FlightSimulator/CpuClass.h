#pragma once

#pragma comment(lib, "pdh.lib")

#include <pdh.h>

class CpuClass
{
public:
	CpuClass();
	CpuClass(const CpuClass&);
	~CpuClass();

	void Initialize();
	void Shutdown();
	void Frame();

	int GetCpuPercentage();

private:
	bool m_bCanReadCpu;
	HQUERY m_hQueryHandle;
	HCOUNTER m_hCounterHandle;
	unsigned long m_lLastSampleTime;
	long m_lCpuUsage;
};