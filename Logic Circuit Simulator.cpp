#include <Windows.h>
#include "App.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	App* emulator = new App();

	int exitCode{ emulator->Run() };

	delete emulator;
	return exitCode;
}