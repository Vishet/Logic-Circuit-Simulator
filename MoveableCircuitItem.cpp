#include "MoveableCircuitItem.h"

MoveableCircuitItem::MoveableCircuitItem(
	const Graphics* pGraphics, 
	const D2D1_COLOR_F bgColor,
	CircuitItem::ItemType itemType
) :
	CircuitItem(bgColor, itemType),
	pGraphics{ pGraphics }
{
}

SignalOutput* MoveableCircuitItem::OnRightClick(const D2D1_POINT_2F& mousePoint)
{
	return nullptr;
}

SignalInput* MoveableCircuitItem::OnRightUp(const D2D1_POINT_2F& mousePoint)
{
	return nullptr;
}