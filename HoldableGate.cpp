#include "HoldableGate.h"

HoldableGate::HoldableGate(
	const Graphics* pGraphics,
	const D2D1_RECT_F& rcItem,
	const D2D1_COLOR_F& bgColor, const D2D1_COLOR_F& textColor,
	const std::wstring& itemText
) :
	HoldableItem( pGraphics, rcItem, bgColor, textColor, itemText)
{
}

CircuitItem* HoldableGate::Drop() const
{
	return nullptr;
}

HoldableGate* HoldableGate::OnClick(const D2D1_POINT_2F& mousePoint) const
{
	if (PointInRect(mousePoint, rcItem))
		return new HoldableGate(pGraphics, rcItem, bgColor, textColor, itemText);

	return nullptr;
}