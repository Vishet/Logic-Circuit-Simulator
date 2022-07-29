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
		const D2D1_COLOR_F bgColor
	);

	virtual MoveableCircuitItem* OnClick(const D2D1_POINT_2F& mousePoint) = 0;
	virtual void Move(const D2D1_POINT_2F& mousePoint) = 0;
	virtual SignalOutput* OnRightClick(const D2D1_POINT_2F& mousePoint) override;
	virtual SignalInput* OnRightUp(const D2D1_POINT_2F& mousePoint) override;

	virtual bool isMouseOverInput(const D2D1_POINT_2F& mousePoint, D2D1_POINT_2F& inputPoint) const override { return false; }
};

