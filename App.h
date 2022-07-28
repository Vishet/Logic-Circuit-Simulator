#pragma once

#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

#include "Line.h"
#include "HoldableItem.h"
#include "MoveableCircuitItem.h"
#include "HoldableAND.h"
#include "HoldableOR.h"
#include "HoldableInput.h"
#include "SignalInput.h"
#include "SignalOutput.h"
#include "HPTimer.h"
#include "VRectangle.h"

#include <thread>
#include <chrono>

class App
{
private:
	Window window{ &keyboard, &mouse };
	Mouse mouse{ &window };
	Keyboard keyboard{};
	Graphics graphics;
	std::vector<LayoutItem*> layoutVector{};
	std::vector<CircuitItem*> circuitVector{};
	std::vector<CircuitItem*> signalLinesVector{};

	HoldableItem* pHoldingItem{};
	MoveableCircuitItem* pHoldingCircuitItem{};

	SignalOutput* pSelectedSignalOutput{};
	SignalInput* pSelectedSignalInput{};

	HPTimer fpsTimer{};
	int frameRate{};

	HPTimer fpsDelayTimer{ 1.0 };

public:
	App() = default;
	App(const App&) = delete;
	App operator=(const App&) = delete;
	~App();

	int Run();

private:
	inline void Update();
	inline void Render();
	inline void DrawFrameRate();

	inline void CreateLayout();

	inline void OnLMBClicked();
	inline void OnLMBReleased();
	inline void OnRMBClicked();
	inline void OnRMBReleased();

	inline void OnLMBDown();
	inline void OnRMBDown();
};

