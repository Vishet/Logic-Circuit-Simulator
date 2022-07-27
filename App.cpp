#include "App.h"

int App::Run()
{
	Graphics::InitializeCOM();

	if (!window.Create(L"Logic Circuit Simulator", WindowClass::ClassName::VCLASS, 800, 600))
		return -1;
	window.Show();

	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Graphics::UnitializeCOM();

	return static_cast<int>(msg.wParam);
}
