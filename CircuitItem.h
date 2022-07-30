#pragma once

#include <d2d1.h>
#include <string>

class SignalOutput;
class SignalInput;

class CircuitItem
{
public:
	enum class ItemType
	{
		NORMAL_GATE,
		INPUT,
		SIGNAL_LINE
	};

protected:
	D2D1_COLOR_F bgColor;
	ItemType itemType;

public:
	CircuitItem(const D2D1_COLOR_F bgColor, ItemType itemType) :
		bgColor{ bgColor },
		itemType{ itemType }
	{
	};

	virtual CircuitItem* OnClick(const D2D1_POINT_2F& mousePoint) = 0;
	virtual SignalOutput* OnRightClick(const D2D1_POINT_2F& mousePoint) = 0;
	virtual SignalInput* OnRightUp(const D2D1_POINT_2F& mousePoint) = 0;
	virtual void Draw() const = 0;

	virtual bool isMouseOverInput(const D2D1_POINT_2F& mousePoint, D2D1_POINT_2F& inputPoint) const { return false; }
	ItemType GetType() const { return itemType; }
};

