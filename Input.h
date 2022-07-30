#pragma once

#include "MoveableCircuitItem.h"
#include "SignalOutput.h"
#include "SignalInput.h"

class Input : public MoveableCircuitItem
{
private:
	D2D1_POINT_2F centerPoint;
	const float radius;
	D2D1_COLOR_F activeColor;
	bool actived{ false };
	SignalOutput signalOutput;

public:
	Input(
		const Graphics* pGraphics,
		const D2D1_POINT_2F& centerPoint,
		const float radius,
		const D2D1_COLOR_F& bgColor,
		const D2D1_COLOR_F& activeColor
	);

	void Draw() const override;
	SignalOutput* GetSignalOutputPtr() { return &signalOutput; }

	MoveableCircuitItem* OnClick(const D2D1_POINT_2F& mousePoint) override;
	SignalOutput* OnRightClick(const D2D1_POINT_2F& mousePoint) override;
	void Move(const D2D1_POINT_2F& mousePoint) override;
};

