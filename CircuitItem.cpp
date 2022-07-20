#include "CircuitItem.h"

CircuitItem::CircuitItem(
	const D2D1_RECT_F& rcItem, 
	const D2D1_COLOR_F bgColor, 
	const std::wstring& itemText,
	const D2D1_COLOR_F textColor
) :
	rcItem{ rcItem },
	bgColor{ bgColor },
	itemText{ itemText },
	textColor{ textColor }
{
}

D2D1_RECT_F CircuitItem::GetItemRect() const
{
	return rcItem;
}
