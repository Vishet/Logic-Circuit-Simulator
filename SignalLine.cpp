#include "SignalLine.h"

SignalLine::SignalLine(const Graphics* pGraphics, const D2D1_POINT_2F& pointA, const D2D1_POINT_2F& pointB, const D2D1_COLOR_F& color, float strokeWidth) :
	pGraphics{ pGraphics },
	pointA{ pointA },
	pointB{ pointB },
	strokeWidth{ strokeWidth },
	CircuitItem(color)
{
}

void SignalLine::Draw() const
{
	pGraphics->DrawLine(pointA, pointB, bgColor, strokeWidth);
}