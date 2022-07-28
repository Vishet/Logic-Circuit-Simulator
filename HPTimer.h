#pragma once

#include <Windows.h>

class HPTimer
{
private:
	LARGE_INTEGER CpuFrequency{};
	LARGE_INTEGER lastCount{};

public:
	HPTimer();
	HPTimer(double startSeconds);
	HPTimer(const HPTimer&) = delete;
	HPTimer operator=(const HPTimer&) = delete;

	void Set();
	double GetElapsedSeconds();
	int GetTickRate();
};

