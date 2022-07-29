#include "SignalLine.h"

SignalLine::SignalLine(const Graphics* pGraphics, const D2D1_POINT_2F& pointA, const D2D1_POINT_2F& pointB, const D2D1_COLOR_F& color, const D2D1_COLOR_F& activeColor, float strokeWidth) :
	pGraphics{ pGraphics },
	pointA{ pointA },
	pointB{ pointB },
	strokeWidth{ strokeWidth },
	activeColor{ activeColor },
	CircuitItem(color)
{
}

void SignalLine::Draw() const
{
	if(status)
		pGraphics->DrawLine(pointA, pointB, activeColor, strokeWidth);
	else
		pGraphics->DrawLine(pointA, pointB, bgColor, strokeWidth);
}