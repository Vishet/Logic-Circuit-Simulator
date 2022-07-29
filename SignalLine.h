#pragma once

#include "CircuitItem.h"
#include "Graphics.h"

class SignalLine : public CircuitItem
{
private:
	const Graphics* pGraphics;
	D2D1_POINT_2F pointA;
	D2D1_POINT_2F pointB;
	D2D1_COLOR_F color;
	D2D1_COLOR_F activeColor;
	float strokeWidth;
	bool status{ false };

public:
	SignalLine(const Graphics* pGraphics, const D2D1_POINT_2F& pointA, const D2D1_POINT_2F& pointB, const D2D1_COLOR_F& color, const D2D1_COLOR_F& activeColor, float strokeWidth);
	SignalLine(const SignalLine&) = delete;
	SignalLine& operator=(const SignalLine&) = delete;

	void ChangePointA(const D2D1_POINT_2F& point) { pointA = point; }
	void ChangePointB(const D2D1_POINT_2F& point) { pointB = point; }
	void SetStatus(bool status) { this->status = status; }

	D2D1_POINT_2F GetPointA() { return pointA; }
	D2D1_POINT_2F GetPointB() { return pointB; }

	void Draw() const override;

	CircuitItem* OnClick(const D2D1_POINT_2F& mousePoint) override { return nullptr; }
	SignalOutput* OnRightClick(const D2D1_POINT_2F& mousePoint) override { return nullptr; }
	SignalInput* OnRightUp(const D2D1_POINT_2F& mousePoint) override  { return nullptr; }
};

