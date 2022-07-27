#pragma once

#include <Windows.h>

class Window;

class Mouse
{
public:
	enum class MouseStatus
	{
		UP,
		PRESSED,
		DOWN,
		RELEASED
	};

private:
	MouseStatus leftButtonStatus{ MouseStatus::UP };
	MouseStatus rightButtonStatus{ MouseStatus::UP };
	int x{};
	int y{};

	const Window* window;

public:
	Mouse(const Window* window);
	Mouse(const Mouse&) = delete;
	Mouse operator=(const Mouse&) = delete;

	void Update();

	POINT GetMousePosition() const;
	int GetX() const { return x; }
	int GetY() const { return y; }

	MouseStatus GetLMBStatus() const { return leftButtonStatus; }
	MouseStatus GetRMBStatus() const { return rightButtonStatus; }

	friend class Window;

private:
	void OnLeftDown();
	void OnLeftUp();
	void OnRightDown();
	void OnRightUp();

	void OnMove(int x, int y);
};

