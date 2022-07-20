#pragma once
#include "HoldableItem.h"

class HoldableGate : public HoldableItem
{
public:
	HoldableGate(
		const Graphics* pGraphics,
		const D2D1_RECT_F& rcItem,
		const D2D1_COLOR_F& bgColor, const D2D1_COLOR_F& textColor,
		const std::wstring& itemText
	);

	CircuitItem* Drop() const override;
	virtual HoldableGate* OnClick(const D2D1_POINT_2F& mousePoint) const override;
};