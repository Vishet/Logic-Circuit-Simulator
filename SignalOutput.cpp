#include "SignalOutput.h"

SignalOutput::SignalOutput(
	const Graphics* pGraphics,
	const D2D1_POINT_2F& position,
	const float radius,
	const D2D1_COLOR_F& bgColor,
	const D2D1_COLOR_F& activeColor
) :
	SignalIO(pGraphics, position, radius, bgColor, activeColor),
	signalLine(pGraphics, position, position, D2D1::ColorF(D2D1::ColorF::LightGray), D2D1::ColorF(D2D1::ColorF::DarkCyan), 2.0f)
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
		pLinkedInput->SetStatus(false);
		pLinkedInput->LinkLine(nullptr);
		pLinkedInput = nullptr;
		signalLine.ChangePointB(signalLine.GetPointA());
	}
}

void SignalOutput::SetStatus(bool status)
{
	if (this->status == status)
		return;

	this->status = status;

	if(pLinkedInput)
		pLinkedInput->SetStatus(this->status);

	signalLine.SetStatus(status);
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
