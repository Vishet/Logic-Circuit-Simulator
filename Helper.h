#pragma once

#include <d2d1.h>

bool inline PointInRect(const D2D1_POINT_2F& point, const D2D1_RECT_F& rect)
{
	D2D1_RECT_F tempRect{ rect };
	if (tempRect.right < tempRect.left)
	{
		float temp{ tempRect.left };
		tempRect.left = tempRect.right;
		tempRect.right = temp;
	}
	if (rect.bottom < rect.top)
	{
		float temp{ tempRect.top };
		tempRect.top = tempRect.bottom;
		tempRect.bottom = temp;
	}

	return (point.x >= tempRect.left && point.x <= tempRect.right && point.y >= tempRect.top && point.y <= tempRect.bottom);
}

double inline DistanceOfTwoPoint(const D2D1_POINT_2F& pointA, const D2D1_POINT_2F& pointB)
{
	return sqrt((pointB.x - pointA.x) * (pointB.x - pointA.x) + (pointB.y - pointA.y) * (pointB.y - pointA.y));
}