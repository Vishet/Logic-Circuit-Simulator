#pragma once

#include "CircuitItem.h"
#include "Graphics.h"

class SignalLine : public CircuitItem
{
private:
	const Graphics* pGraphics;
	D2D1_POINT_2F pointA;
	D2D1_POINT_2F pointB;
	D2D1_COLOR_F activeColor;
	float strokeWidth;
	bool status{ false };
	SignalLine* linkedSignalLine{ nullptr };
	bool directionLocked{ false };

public:
	SignalLine(const Graphics* pGraphics, const D2D1_POINT_2F& pointA, const D2D1_POINT_2F& pointB, const D2D1_COLOR_F& color, const D2D1_COLOR_F& activeColor, float strokeWidth);
	SignalLine(const SignalLine&) = delete;
	SignalLine& operator=(const SignalLine&) = delete;
	~SignalLine();

	void ChangePointA(const D2D1_POINT_2F& point) { pointA = point; }
	void ChangePointB(const D2D1_POINT_2F& point);
	void SetStatus(bool status);

	void SetLockDirection(bool lock);
	void CreateLinkLine();
	void Reset();

	D2D1_POINT_2F GetPointA() const { return pointA; }
	D2D1_POINT_2F GetPointB() const { return pointB; }
	bool IsHorizontalDirection() const;
	bool IsDirectionLocked() const { return directionLocked; }
	SignalLine* GetLinkedLine() const { return linkedSignalLine; }
	SignalLine* GetLastLine();

	void Draw() const override;

	CircuitItem* OnClick(const D2D1_POINT_2F& mousePoint) override { return nullptr; }
	SignalOutput* OnRightClick(const D2D1_POINT_2F& mousePoint) override { return nullptr; }
	SignalInput* OnRightUp(const D2D1_POINT_2F& mousePoint) override  { return nullptr; }
};

