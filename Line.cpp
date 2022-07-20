#include "Line.h"

Line::Line(const Graphics* pGraphics, const D2D1_POINT_2F& pointA, const D2D1_POINT_2F& pointB, const D2D1_COLOR_F& color, float strokeWidth) :
	pGraphics{ pGraphics },
	pointA{ pointA },
	pointB{ pointB },
	color{ color },
	strokeWidth{ strokeWidth }
{
	itemType = ItemType::Line;
}

void Line::Draw() const
{
	pGraphics->DrawLine(pointA, pointB, color, strokeWidth);
}