#include "ANDGate.h"

ANDGate::ANDGate(
	const Graphics* pGraphics, 
	const D2D1_RECT_F& rcItem, 
	const D2D1_COLOR_F bgColor, 
	const D2D1_COLOR_F textColor
) :
	NormalGate(pGraphics, rcItem, bgColor, textColor, L"AND")
{
}