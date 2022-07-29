#include "NormalGate.h"

NormalGate::NormalGate(
	const Graphics* pGraphics,
	const D2D1_RECT_F& rcItem,
	const D2D1_COLOR_F& bgColor,
	const D2D1_COLOR_F& textColor,
	const std::wstring& itemText
) :
	MoveableCircuitItem(pGraphics, bgColor),
	rcItem{ rcItem },
	textColor{ textColor },
	itemText{ itemText },
	inputA{ SignalInput(
		pGraphics,
		D2D1::Point2F(rcItem.left, (rcItem.bottom - rcItem.top) / 8 + rcItem.top),
		ioRadius, D2D1::ColorF(D2D1::ColorF::Gray), D2D1::ColorF(D2D1::ColorF::DarkCyan)
	) },
	inputB{ SignalInput(
		pGraphics,
		D2D1::Point2F(rcItem.left, (rcItem.bottom - rcItem.top) * 7 / 8 + rcItem.top),
		ioRadius, D2D1::ColorF(D2D1::ColorF::Gray), D2D1::ColorF(D2D1::ColorF::DarkCyan)
	) }
{
}

void NormalGate::Draw() const
{
	pGraphics->FillRectangle(rcItem, bgColor);
	pGraphics->DrawWString(itemText, textColor, rcItem);
	inputA.Draw();
	inputB.Draw();
}

SignalInput* NormalGate::OnRightUp(const D2D1_POINT_2F& mousePoint)
{
	if (DistanceOfTwoPoint(mousePoint, inputA.GetPosition()) <= ioRadius && !inputA.isLinked())
		return &inputA;
	else if (DistanceOfTwoPoint(mousePoint, inputB.GetPosition()) <= ioRadius && !inputB.isLinked())
		return &inputB;

	return nullptr;
}

MoveableCircuitItem* NormalGate::OnClick(const D2D1_POINT_2F& mousePoint)
{
	if (PointInRect(mousePoint, rcItem))
	{
		mouseOffset.x = mousePoint.x - rcItem.left;
		mouseOffset.y = mousePoint.y - rcItem.top;
		return this;
	}

	return nullptr;
}

void NormalGate::Move(const D2D1_POINT_2F& mousePoint)
{	
	const float width{ rcItem.right - rcItem.left };
	const float height{ rcItem.bottom - rcItem.top };

	rcItem.left = mousePoint.x - mouseOffset.x;
	rcItem.top = mousePoint.y - mouseOffset.y;
	rcItem.right = rcItem.left + width;
	rcItem.bottom = rcItem.top + height;

	inputA.Move(D2D1::Point2F(
		rcItem.left,
		(rcItem.bottom - rcItem.top) / 8 + rcItem.top
	));
	inputB.Move(D2D1::Point2F(
		rcItem.left,
		(rcItem.bottom - rcItem.top) * 7 / 8 + rcItem.top
	));
}