#pragma once

#include "LayoutItem.h"
#include "Graphics.h"

#include <Windows.h>

class Line : public LayoutItem
{
private:
	const Graphics* pGraphics;
	D2D1_POINT_2F pointA;
	D2D1_POINT_2F pointB;
	D2D1_COLOR_F color;
	float strokeWidth;

public:
	Line(const Graphics* pGraphics, const D2D1_POINT_2F& pointA, const D2D1_POINT_2F& pointB, const D2D1_COLOR_F& color, float strokeWidth);
	Line(const Line&) = delete;
	Line& operator=(const Line&) = delete;

	void ChangePointA(const D2D1_POINT_2F& point) { pointA = point; }
	void ChangePointB(const D2D1_POINT_2F& point) { pointB = point; }
	D2D1_POINT_2F GetPointA() { return pointA; }
	D2D1_POINT_2F GetPointB() { return pointB; }

	void Draw() const override;
};

