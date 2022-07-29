#include "SignalIO.h"

SignalIO::SignalIO(
	const Graphics* pGraphics,
	const D2D1_POINT_2F& position,
	const float radius,
	const D2D1_COLOR_F& bgColor,
	const D2D1_COLOR_F& activeColor
) :
	pGraphics{ pGraphics },
	position{ position },
	radius{ radius },
	bgColor{ bgColor },
	activeColor{ activeColor }
{
}

void SignalIO::Draw() const
{
	if(status)
		pGraphics->FillCircle(
			D2D1::Point2F(position.x, position.y),
			radius,
			activeColor
		);
	else
		pGraphics->FillCircle(
			D2D1::Point2F(position.x, position.y),
			radius,
			bgColor
		);
}

void SignalIO::SetStatus(bool status)
{
	this->status = status;
}