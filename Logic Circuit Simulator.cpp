#include "Window.h"
#include "Graphics.h"
#include <Windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Graphics::InitializeCOM();

	Window* mainWindow{ new Window() };
	mainWindow->Create(L"Logic Circuit Simulator", WindowClass::ClassName::VCLASS, 800, 600);
	mainWindow->Show();

	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	delete mainWindow;
	WindowClass::UnregisterAllClasses();
	Graphics::UnitializeCOM();

	return static_cast<int>(msg.wParam);
}