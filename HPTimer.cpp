#include "HPTimer.h"

HPTimer::HPTimer()
{
	QueryPerformanceFrequency(&CpuFrequency);
	QueryPerformanceCounter(&lastCount);
}

HPTimer::HPTimer(double startSeconds)
{
	QueryPerformanceFrequency(&CpuFrequency);
	QueryPerformanceCounter(&lastCount);
	lastCount.QuadPart -= CpuFrequency.QuadPart;
}

void HPTimer::Set()
{
	QueryPerformanceCounter(&lastCount);
}

double HPTimer::GetElapsedSeconds()
{
	LARGE_INTEGER currentCount{};
	QueryPerformanceCounter(&currentCount);

	return static_cast<double>(currentCount.QuadPart - lastCount.QuadPart) / CpuFrequency.QuadPart;
}

int HPTimer::GetTickRate()
{
	return 1.0 / GetElapsedSeconds();
}


