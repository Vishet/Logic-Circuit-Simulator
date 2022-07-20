#pragma once

#include "HoldableItem.h"
#include "ANDGate.h"

class HoldableAND : public HoldableItem
{
public:
	HoldableAND(
		const Graphics* pGraphics,
		const D2D1_RECT_F& rcItem,
		const D2D1_COLOR_F& bgColor, const D2D1_COLOR_F& textColor
	);

	HoldableItem* OnClick(const D2D1_POINT_2F& mousePoint) const override;
	CircuitItem* Drop() const override;
};

