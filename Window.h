#pragma once

#include "WindowClass.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <Windows.h>
#include <Windowsx.h> // GET_X_LPARAM / GET_Y_LPARAM
#include <optional>

class Window
{
private:
	HWND hWindow{};

	float width{};
	float height{};
	float ncWidth{};
	float ncHeight{};

	Keyboard* keyboard;
	Mouse* mouse;

public:
	Window(Keyboard* keyboard, Mouse* mouse);
	Window(const Window&) = delete;
	Window operator=(const Window&) = delete;
	~Window();

	bool Create(const wchar_t* szWindowName, WindowClass::ClassName className, int width, int height, int x = 0, int y = 0);
	void Destroy();

	void Show() const;
	void Hide() const;

	HWND GetHwnd() const { return hWindow; }
	float GetWidth() const { return width; }
	float GetHeight() const { return height; }
	float GetNCWidth() const { return ncWidth; }
	float GetNCHeight() const { return ncHeight; }

	std::optional<WPARAM> ProcessMessages();

	static LRESULT CALLBACK WndProcSetup(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WndProc(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


