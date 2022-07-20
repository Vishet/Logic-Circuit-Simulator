#pragma once

#include "HoldableItem.h"
#include "Input.h"

class HoldableInput : public HoldableItem
{
private:
	D2D1_POINT_2F centerPoint;
	float radius;
	D2D1_COLOR_F activeColor;

public:
	HoldableInput(
		const Graphics* pGraphics,
		const D2D1_POINT_2F& centerPoint,
		const float radius,
		const D2D1_COLOR_F& bgColor,
		const D2D1_COLOR_F& activeColor
	);
	HoldableInput(const HoldableInput&) = delete;
	const HoldableInput& operator=(const HoldableInput&) = delete;

	CircuitItem* Drop() const override;
	HoldableItem* OnClick(const D2D1_POINT_2F& mousePoint) const override;
	void Draw() const override;
	void Move(const D2D1_POINT_2F& mousePoint) override;
};

