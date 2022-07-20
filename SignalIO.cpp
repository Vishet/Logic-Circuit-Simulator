#include "SignalIO.h"

SignalIO::SignalIO(
	const Graphics* pGraphics,
	const D2D1_POINT_2F& offsetPosition,
	const float radius,
	const D2D1_COLOR_F& bgColor
) :
	pGraphics{ pGraphics },
	offsetPosition{ offsetPosition },
	radius{ radius },
	bgColor{ bgColor }
{
}

void SignalIO::Draw(const D2D1_RECT_F& parentRect) const
{
	pGraphics->FillCircle(
		D2D1::Point2F(parentRect.left + offsetPosition.x, parentRect.top + offsetPosition.y),
		radius,
		bgColor
	);
}

void SignalIO::SetStatus(bool status)
{
	this->status = status;
}