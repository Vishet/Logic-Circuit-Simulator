#pragma once

#include "WindowClass.h"
#include "Graphics.h"
#include "LayoutItem.h"
#include "HoldableItem.h"
#include "Line.h"
#include "HoldableAND.h"
#include "HoldableOR.h"
#include "HoldableInput.h"
#include "MoveableCircuitItem.h"
#include "Input.h"
#include "SignalInput.h"
#include "SignalOutput.h"
#include "SignalLine.h"
#include <Windows.h>
#include <vector>
#include <Windowsx.h>
#include "Keyboard.h"
#include "Mouse.h"

#define MOUSEMOVE_LMB 0x0001
#define MOUSEMOVE_RMB 0x0002

class Window
{
private:
	HWND hWindow{};
	Graphics* pGraphics{ new Graphics() };
	std::vector<LayoutItem*> layoutVector{};
	std::vector<CircuitItem*> circuitVector{};
	std::vector<CircuitItem*> signalLinesVector{};
	float nWidth{};
	float nHeight{};
	bool lmbPrevious{ false };
	bool rmbPrevious{ false };

	HoldableItem* pHoldingItem{};
	MoveableCircuitItem* pHoldingCircuitItem{};

	SignalOutput* pSelectedSignalOutput{};
	SignalInput* pSelectedSignalInput{};

	bool Update() const;

	Keyboard* keyboard;
	Mouse* mouse;

public:
	Window(Keyboard* keyboard, Mouse* mouse);
	Window(const Window&) = delete;
	Window operator=(const Window&) = delete;
	~Window();

	bool Create(const wchar_t* szWindowName, WindowClass::ClassName className, int nWidth, int nHeight, int x = 0, int y = 0);
	void Destroy();

	void Show() const;
	void Hide() const;

	static LRESULT CALLBACK WndProcSetup(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WndProc(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


