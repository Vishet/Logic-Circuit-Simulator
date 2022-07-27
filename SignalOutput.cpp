#include "SignalOutput.h"

SignalOutput::SignalOutput(
	const Graphics* pGraphics,
	const D2D1_POINT_2F& position,
	const float radius,
	const D2D1_COLOR_F& bgColor
) :
	SignalIO(pGraphics, position, radius, bgColor),
	signalLine(pGraphics, position, position, D2D1::ColorF(D2D1::ColorF::LightGray), 2.0f)
{
}

void SignalOutput::LinkInput(SignalInput* pInput)
{
	if (pInput)
	{
		pLinkedInput = pInput;
		pLinkedInput->SetStatus(this->status);
		signalLine.ChangePointB(pInput->GetPosition());
	}
	else if(pLinkedInput)
	{
		pLinkedInput->LinkLine(nullptr);
		pLinkedInput = nullptr;
		signalLine.ChangePointB(signalLine.GetPointA());
	}
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

void SignalOutput::Draw() const
{
	SignalIO::Draw();
}

void SignalOutput::Move(const D2D1_POINT_2F& ptMoveTo)
{
	SignalIO::Move(ptMoveTo);
	signalLine.ChangePointA(position);
	if (!pLinkedInput)
		signalLine.ChangePointB(position);
}
