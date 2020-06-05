#include "CpuClass.h"

CpuClass::CpuClass()
{
}

CpuClass::CpuClass(const CpuClass& other)
{
}

CpuClass::~CpuClass()
{
}

void CpuClass::Initialize()
{
	PDH_STATUS status;
	// Initialize the flag indicating whether this object can read the system cpu usage or not.
	m_bCanReadCpu = true;
	// Create a query object to poll cpu usage.
	status = PdhOpenQuery(NULL, 0, &m_hQueryHandle);
	if (status != ERROR_SUCCESS)
	{
		m_bCanReadCpu = false;
	}
	// Set query object to poll all cpus in the system.
	status = PdhAddCounter(m_hQueryHandle, TEXT("\\Processor(_Total)\\% processor time"), 0,
		&m_hCounterHandle);
	if (status != ERROR_SUCCESS)
	{
		m_bCanReadCpu = false;
	}
	m_lLastSampleTime = GetTickCount();
	m_lCpuUsage = 0;
	return;
}

void CpuClass::Shutdown()
{
	if (m_bCanReadCpu)
	{
		PdhCloseQuery(m_hQueryHandle);
	}
	return;
}

void CpuClass::Frame()
{
	PDH_FMT_COUNTERVALUE value;
	if (m_bCanReadCpu)
	{
		if ((m_lLastSampleTime + 1000) < GetTickCount())
		{
			m_lLastSampleTime = GetTickCount();
			PdhCollectQueryData(m_hQueryHandle);

			PdhGetFormattedCounterValue(m_hCounterHandle, PDH_FMT_LONG, NULL, &value);
			m_lCpuUsage = value.longValue;
		}
	}
	return;
}

int CpuClass::GetCpuPercentage()
{
	int usage;
	if (m_bCanReadCpu)
	{
		usage = (int)m_lCpuUsage;
	}
	else
	{
		usage = 0;
	}
	return usage;
}