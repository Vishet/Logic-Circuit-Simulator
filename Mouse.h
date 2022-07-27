#pragma once

#include <Windows.h>

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

	void OnLeftDown();
	void OnLeftUp();
	void OnRightDown();
	void OnRightUp();

	void OnMove(int x, int y);

public:
	Mouse();
	Mouse(const Mouse&) = delete;
	Mouse operator=(const Mouse&) = delete;

	void Update();

	POINT GetMousePosition() const;
	int GetX() const { return x; }
	int GetY() const { return y; }

	friend class Window;
};

