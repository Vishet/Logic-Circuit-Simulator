#include "WindowClass.h"

std::bitset<WindowClass::ClassName::MAX_CLASS> rgRegisteredClasses{};

void WindowClass::GetEnumString(WindowClass::ClassName classNameEnum, std::wstring &outputString) noexcept
{
	switch (classNameEnum)
	{
	case VCLASS: 
		outputString.assign(L"VCLASS");
		break;
	default: 
		outputString.assign(L"ERROR");
	}
}

void WindowClass::RegisterMyClass(ClassName className, WNDPROC pWindowProcedure) noexcept
{
	std::wstring classNameString{};
	GetEnumString(className, classNameString);
	const wchar_t* szClassName{ classNameString.c_str() };

	if (rgRegisteredClasses.test(className))
		UnregisterClass(szClassName, GetModuleHandle(0));

	WNDCLASSEX wndClass{ 0 };
	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = GetModuleHandle(0);
	wndClass.lpfnWndProc = pWindowProcedure;
	wndClass.lpszClassName = szClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	RegisterClassEx(&wndClass);
}

void WindowClass::UnregisterAllClasses() noexcept
{
	for (size_t i{ 0 }; i < ClassName::MAX_CLASS; i++)
	{
		std::wstring classNameString{};
		GetEnumString(static_cast<ClassName>(i), classNameString);
		const wchar_t* szClassName{ classNameString.c_str() };

		if (rgRegisteredClasses.test(i))
			UnregisterClass(szClassName, GetModuleHandle(0));
	}
}