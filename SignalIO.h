#pragma once

#include "Graphics.h"
#include "Line.h"

#include <d2d1.h>

class SignalIO
{
protected:
	const Graphics* pGraphics;
	D2D1_POINT_2F position;
	const float radius;
	const D2D1_COLOR_F bgColor;
	bool status{ false };

public:
	SignalIO(
		const Graphics* pGraphics,
		const D2D1_POINT_2F& position,
		const float radius,
		const D2D1_COLOR_F& bgColor
	);

	virtual void Draw() const;
	virtual void SetStatus(bool status);
	virtual void Move(const D2D1_POINT_2F& ptMoveTo) { position = ptMoveTo; }
	D2D1_POINT_2F GetPosition() const { return position; }
};

