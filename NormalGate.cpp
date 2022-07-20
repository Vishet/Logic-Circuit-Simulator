#include "NormalGate.h"

NormalGate::NormalGate(
	const Graphics* pGraphics,
	const D2D1_RECT_F& rcItem,
	const D2D1_COLOR_F bgColor,
	const D2D1_COLOR_F textColor,
	const std::wstring& itemText
) :
	MoveableCircuitItem(pGraphics, rcItem, bgColor, itemText.c_str(), textColor),
	inputA{ SignalInput(
		pGraphics,
		D2D1::Point2F(0, (rcItem.bottom - rcItem.top) / 8),
		ioRadius, D2D1::ColorF(D2D1::ColorF::Gray)
	) },
	inputB{ SignalInput(
		pGraphics,
		D2D1::Point2F(0, (rcItem.bottom - rcItem.top) * 7 / 8),
		ioRadius, D2D1::ColorF(D2D1::ColorF::Gray)
	) }
{
}

void NormalGate::Draw() const
{
	pGraphics->FillRectangle(rcItem, bgColor);
	pGraphics->DrawWString(itemText, textColor, rcItem);
	inputA.Draw(rcItem);
	inputB.Draw(rcItem);
}

SignalInput* NormalGate::OnRightUp(const D2D1_POINT_2F& mousePoint)
{
	if (DistanceOfTwoPoint(mousePoint, inputA.GetPosition()) <= ioRadius)
		return &inputA;
	else if (DistanceOfTwoPoint(mousePoint, inputB.GetPosition()) <= ioRadius)
		return &inputB;

	return nullptr;
}
