#include "HoldableInput.h"

HoldableInput::HoldableInput(
	const Graphics* pGraphics,
	const D2D1_POINT_2F& centerPoint,
	const float radius,
	const D2D1_COLOR_F& bgColor,
	const D2D1_COLOR_F& activeColor
) :
	HoldableItem(pGraphics, D2D1::RectF(), bgColor, D2D1::ColorF(D2D1::ColorF::White), L""),
	centerPoint{ centerPoint },
	radius{ radius },
	activeColor{ activeColor }
{
}

CircuitItem* HoldableInput::Drop() const
{
	return new Input(pGraphics, centerPoint, radius, bgColor, activeColor);
}

HoldableItem* HoldableInput::OnClick(const D2D1_POINT_2F& mousePoint) const
{
	if (DistanceOfTwoPoint(mousePoint, centerPoint) <= radius)
		return new HoldableInput(
			pGraphics,
			mousePoint,
			radius,
			bgColor,
			activeColor
		);

	return nullptr;
}

void HoldableInput::Draw() const
{
	pGraphics->FillCircle(centerPoint, radius, bgColor);
}

void HoldableInput::Move(const D2D1_POINT_2F& mousePoint)
{
	centerPoint = mousePoint;
}