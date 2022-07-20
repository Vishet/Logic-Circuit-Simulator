#pragma once

#include <d2d1.h>
#include <string>

class SignalOutput;
class SignalInput;

class CircuitItem
{
protected:
	D2D1_RECT_F rcItem;
	D2D1_COLOR_F bgColor;
	std::wstring itemText;
	D2D1_COLOR_F textColor;

public:
	CircuitItem(
		const D2D1_RECT_F& rcItem, 
		const D2D1_COLOR_F bgColor, 
		const std::wstring& itemText,
		const D2D1_COLOR_F textColor
	);

	virtual CircuitItem* OnClick(const D2D1_POINT_2F& mousePoint) = 0;
	virtual SignalOutput* OnRightClick(const D2D1_POINT_2F& mousePoint) = 0;
	virtual SignalInput* OnRightUp(const D2D1_POINT_2F& mousePoint) = 0;
	virtual void Move(const D2D1_POINT_2F& mousePoint) = 0;
	virtual void Draw() const = 0;
	D2D1_RECT_F GetItemRect() const;
};

