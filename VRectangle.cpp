#include "VRectangle.h"

VRectangle::VRectangle(const Graphics* graphics, const D2D1_RECT_F& rect, const D2D1_COLOR_F& bgColor) :
	graphics{ graphics },
	rect{ rect },
	bgColor{ bgColor }
{
	itemType = ItemType::Rectangle;
}

void VRectangle::Draw() const
{
	graphics->FillRectangle(rect, bgColor);
}
