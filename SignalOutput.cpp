#include "SignalOutput.h"

SignalOutput::SignalOutput(
	const Graphics* pGraphics,
	const D2D1_POINT_2F& offsetPosition,
	const float radius,
	const D2D1_COLOR_F& bgColor,
	const D2D1_POINT_2F& position
) :
	SignalIO(pGraphics, offsetPosition, radius, bgColor),
	signalLine(pGraphics, position, position, D2D1::ColorF(D2D1::ColorF::LightGray), 2.0f)
{
}

void SignalOutput::LinkInput(SignalInput* pInput)
{
	pLinkedInput = pInput;
	pLinkedInput->SetStatus(this->status);
	signalLine.ChangePointB(pInput->GetPosition());
}

void SignalOutput::SetStatus(bool status)
{
	this->status = status;
	pLinkedInput->SetStatus(this->status);
}

void SignalOutput::UpdateLine(const D2D1_POINT_2F& newPoint)
{
	signalLine.ChangePointB(newPoint);
}

void SignalOutput::UpdateLine()
{
	signalLine.ChangePointB(signalLine.GetPointA());
}

void SignalOutput::Draw(const D2D1_RECT_F& parentRect) const
{
	pGraphics->FillCircle(
		D2D1::Point2F(parentRect.left + offsetPosition.x, parentRect.top + offsetPosition.y),
		radius,
		bgColor
	);
	signalLine.Draw();
}

