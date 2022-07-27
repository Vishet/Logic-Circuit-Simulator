#include "Window.h"

Window::Window(Keyboard* keyboard, Mouse* mouse) :
	keyboard{ keyboard },
	mouse{ mouse }
{
}

Window::~Window()
{
}

bool Window::Create(const wchar_t* szWindowName, WindowClass::ClassName className, int width, int height, int x, int y)
{
	WindowClass::RegisterMyClass(className, WndProcSetup);

	std::wstring classNameString{};
	WindowClass::GetEnumString(className, classNameString);
	const wchar_t* szClassName{ classNameString.c_str() };

	this->width = static_cast<float>(width);
	this->height = static_cast<float>(height);

	RECT rcWnd{};
	rcWnd.right = width;
	rcWnd.bottom = height;
	AdjustWindowRect(&rcWnd, WS_OVERLAPPEDWINDOW, false);

	ncWidth = rcWnd.right - rcWnd.left;
	ncHeight = rcWnd.bottom - rcWnd.top;

	hWindow = CreateWindowExW(
		NULL,
		szClassName, szWindowName,
		WS_OVERLAPPEDWINDOW,
		x, y, ncWidth, ncHeight,
		NULL, NULL, GetModuleHandle(0), this 
	);

	return true;
}

void Window::Destroy()
{
	DestroyWindow(hWindow);
}

void Window::Show() const
{
	ShowWindow(hWindow, SW_SHOW);
}

void Window::Hide() const
{
	ShowWindow(hWindow, SW_HIDE);
}

std::optional<WPARAM> Window::ProcessMessages()
{
	MSG msg{};
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT) return msg.wParam;
	}

	return {};
}

LRESULT Window::WndProcSetup(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate{ reinterpret_cast<CREATESTRUCT*>(lParam) };
		Window* creatorWindow{ static_cast<Window*>(pCreate->lpCreateParams) };
		SetWindowLongPtr(hWindow, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(creatorWindow));
		creatorWindow->hWindow = hWindow;

		return creatorWindow->WndProc(hWindow, uMsg, wParam, lParam);
	}
	else
	{
		Window* creatorWindow{ reinterpret_cast<Window*>(GetWindowLongPtr(hWindow, GWLP_USERDATA)) };
		if(creatorWindow)
			return creatorWindow->WndProc(hWindow, uMsg, wParam, lParam);
		else
			return DefWindowProc(hWindow, uMsg, wParam, lParam);
	}
}

LRESULT Window::WndProc(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		mouse->OnLeftDown();
		return 0;

	case WM_LBUTTONUP:
		mouse->OnLeftUp();
		return 0;

	case WM_RBUTTONDOWN:
		mouse->OnRightDown();
		return 0;

	case WM_RBUTTONUP:
	{
		mouse->OnRightUp();
		return 0;
	}

	case WM_MOUSEMOVE:
		mouse->OnMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
		if (!(HIWORD(lParam) & 0x4000))
			keyboard->OnKeyDown(static_cast<int>(wParam));
		return 0;

	case WM_KEYUP:
		keyboard->OnKeyUp(static_cast<int>(wParam));
		return 0;

	case WM_KILLFOCUS:
		keyboard->Flush();
		return 0;

	default:
		return DefWindowProc(hWindow, uMsg, wParam, lParam);
	}

	return 0;
}