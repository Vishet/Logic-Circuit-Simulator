#include "HoldableOR.h"

HoldableOR::HoldableOR(
	const Graphics* pGraphics,
	const D2D1_RECT_F& rcItem,
	const D2D1_COLOR_F& bgColor,
	const D2D1_COLOR_F& textColor
) :
	HoldableItem(pGraphics, rcItem, bgColor, textColor, L"OR")
{
}

HoldableItem* HoldableOR::OnClick(const D2D1_POINT_2F& mousePoint) const
{
	if (PointInRect(mousePoint, rcItem))
		return new HoldableOR(
			pGraphics,
			D2D1::RectF(
				mousePoint.x - (rcItem.right - rcItem.left) / 2,
				mousePoint.y - (rcItem.bottom - rcItem.top) / 2,
				mousePoint.x + (rcItem.right - rcItem.left) / 2,
				mousePoint.y + (rcItem.bottom - rcItem.top) / 2
			),
			bgColor, textColor
		);

	return nullptr;
}

CircuitItem* HoldableOR::Drop() const
{
	return new ORGate(pGraphics, rcItem, bgColor, textColor);
}
