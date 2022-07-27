#include "HPTimer.h"

HPTimer::HPTimer()
{
	auto teste = QueryPerformanceFrequency(&CpuFrequency);
}

void HPTimer::Set()
{
	QueryPerformanceCounter(&lastCount);
}

double HPTimer::GetElapsedTime()
{
	LARGE_INTEGER currentCount{};
	QueryPerformanceCounter(&currentCount);

	return static_cast<double>(currentCount.QuadPart - lastCount.QuadPart) / CpuFrequency.QuadPart;
}

double HPTimer::GetTickRate()
{
	LARGE_INTEGER currentCount{};
	QueryPerformanceCounter(&currentCount);

	return static_cast<double>(currentCount.QuadPart - lastCount.QuadPart) * 1000000 / CpuFrequency.QuadPart;
}

