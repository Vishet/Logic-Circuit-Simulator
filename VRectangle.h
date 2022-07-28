#pragma once

#include "LayoutItem.h"
#include "Graphics.h"

class VRectangle : public LayoutItem
{
private:
	const Graphics* graphics;
	D2D1_RECT_F rect;
	D2D1_COLOR_F bgColor;

public:
	VRectangle(const Graphics* graphics, const D2D1_RECT_F& rect, const D2D1_COLOR_F& bgColor);
	VRectangle(const VRectangle&) = delete;
	VRectangle operator=(const VRectangle&) = delete;

	void Draw() const override;
};

