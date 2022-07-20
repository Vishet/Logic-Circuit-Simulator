#include "MoveableCircuitItem.h"

MoveableCircuitItem::MoveableCircuitItem(
	const Graphics* pGraphics, 
	const D2D1_RECT_F& rcItem, 
	const D2D1_COLOR_F bgColor, 
	const std::wstring& itemText,
	const D2D1_COLOR_F textColor
) :
	CircuitItem(rcItem, bgColor, itemText, textColor),
	pGraphics{ pGraphics }
{
}

MoveableCircuitItem* MoveableCircuitItem::OnClick(const D2D1_POINT_2F& mousePoint)
{
	if (PointInRect(mousePoint, rcItem))
	{
		mouseOffset.x = mousePoint.x - rcItem.left;
		mouseOffset.y = mousePoint.y - rcItem.top;
		return this;
	}

	return nullptr;
}

void MoveableCircuitItem::Move(const D2D1_POINT_2F& mousePoint)
{
	const float width{ rcItem.right - rcItem.left };
	const float height{ rcItem.bottom - rcItem.top };

	rcItem.left = mousePoint.x - mouseOffset.x;
	rcItem.top = mousePoint.y - mouseOffset.y;
	rcItem.right = rcItem.left + width;
	rcItem.bottom = rcItem.top + height;
}


SignalOutput* MoveableCircuitItem::OnRightClick(const D2D1_POINT_2F& mousePoint)
{
	return nullptr;
}

SignalInput* MoveableCircuitItem::OnRightUp(const D2D1_POINT_2F& mousePoint)
{
	return nullptr;
}