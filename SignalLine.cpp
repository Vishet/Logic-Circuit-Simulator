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

void SignalLine::ChangePointB(const D2D1_POINT_2F& point)
{
	if (!directionLocked)
	{
		pointB.x = point.x;
		pointB.y = point.y;
		return;
	}

	if (abs(point.x - pointA.x) >= abs(point.y - pointA.y))
	{
		pointB.x = point.x;
		pointB.y = pointA.y;
	}
	else
	{
		pointB.y = point.y;
		pointB.x = pointA.x;
	}		
}

void SignalLine::Draw() const
{
	if(status)
		pGraphics->DrawLine(pointA, pointB, activeColor, strokeWidth);
	else
		pGraphics->DrawLine(pointA, pointB, bgColor, strokeWidth);
}