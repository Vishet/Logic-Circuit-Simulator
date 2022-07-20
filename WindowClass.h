#pragma once

#include <Windows.h>
#include <bitset>
#include <string>

class WindowClass
{
public:
	enum ClassName
	{
		VCLASS,
		MAX_CLASS
	};
	static void GetEnumString(ClassName classNameEnum, std::wstring& outputString) noexcept;

private:
	static std::bitset<ClassName::MAX_CLASS> bsRegisteredClasses;
	WindowClass(){};
	~WindowClass(){};

public:
	static void RegisterMyClass(ClassName className, WNDPROC pWindowProcedure) noexcept;
	static void UnregisterAllClasses() noexcept;
};

