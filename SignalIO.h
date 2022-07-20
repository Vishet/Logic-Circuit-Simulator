#pragma once

#include "Graphics.h"
#include "Line.h"

#include <d2d1.h>

class SignalIO
{
protected:
	const Graphics* pGraphics;
	D2D1_POINT_2F offsetPosition;
	const float radius;
	const D2D1_COLOR_F bgColor;
	bool status{ false };

public:
	SignalIO(
		const Graphics* pGraphics,
		const D2D1_POINT_2F& offsetPosition,
		const float radius,
		const D2D1_COLOR_F& bgColor
	);

	virtual void Draw(const D2D1_RECT_F& parentRect) const;
	virtual void SetStatus(bool status);
	D2D1_POINT_2F GetPosition() const { return offsetPosition; }
};

