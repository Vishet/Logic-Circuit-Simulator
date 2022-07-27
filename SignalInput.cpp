#include "SignalInput.h"

SignalInput::SignalInput(
	const Graphics* pGraphics,
	const D2D1_POINT_2F& position, 
	const float radius,
	const D2D1_COLOR_F& bgColor
) :
	SignalIO(pGraphics, position, radius, bgColor)
{
}

void SignalInput::Move(const D2D1_POINT_2F& ptMoveTo)
{
	SignalIO::Move(ptMoveTo);
	if (signalLine)
		signalLine->ChangePointB(position);
}

void SignalInput::Draw() const
{
	SignalIO::Draw();
}