#pragma once

#include "CircuitItem.h"
#include "Graphics.h"
#include "Helper.h"
#include "SignalIO.h"

class MoveableCircuitItem : public CircuitItem
{
protected:
	const Graphics* pGraphics;
	D2D1_POINT_2F mouseOffset{};

public:
	MoveableCircuitItem(
		const Graphics* pGraphics,
		const D2D1_RECT_F& rcItem,
		const D2D1_COLOR_F bgColor,
		const std::wstring& itemText,
		const D2D1_COLOR_F textColor
	);

	virtual MoveableCircuitItem* OnClick(const D2D1_POINT_2F& mousePoint);
	virtual void Move(const D2D1_POINT_2F& mousePoint);
	virtual SignalOutput* OnRightClick(const D2D1_POINT_2F& mousePoint) override;
	virtual SignalInput* OnRightUp(const D2D1_POINT_2F& mousePoint) override;
};

