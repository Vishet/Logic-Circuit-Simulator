#include "Input.h"

Input::Input(
	const Graphics* pGraphics,
	const D2D1_POINT_2F& centerPoint,
	const float radius,
	const D2D1_COLOR_F& bgColor,
	const D2D1_COLOR_F& activeColor
) :
	MoveableCircuitItem(pGraphics, bgColor),
	centerPoint{ centerPoint },
	radius{ radius },
	activeColor{ activeColor },
	signalOutput{ pGraphics, centerPoint, 0.0f, D2D1::ColorF(D2D1::ColorF::Gray), D2D1::ColorF(D2D1::ColorF::DarkCyan) }
{
}

void Input::Draw() const
{
	signalOutput.Draw();
	if(actived)
		pGraphics->FillCircle(centerPoint, radius, activeColor);
	else
		pGraphics->FillCircle(centerPoint, radius, bgColor);
}

MoveableCircuitItem* Input::OnClick(const D2D1_POINT_2F& mousePoint)
{
	if (DistanceOfTwoPoint(mousePoint, centerPoint) <= radius)
	{
		if (GetKeyState(VK_LCONTROL) & 0x8000 && GetKeyState(VK_LBUTTON) & 0x8000)
		{
			mouseOffset.x = mousePoint.x - centerPoint.x;
			mouseOffset.y = mousePoint.y - centerPoint.y;
			return this;
		}
		else if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			actived = !actived;
			signalOutput.SetStatus(actived);
		}
			
	}

	return nullptr;
}

SignalOutput* Input::OnRightClick(const D2D1_POINT_2F& mousePoint)
{
	if (DistanceOfTwoPoint(mousePoint, centerPoint) <= radius)
	{
		signalOutput.UpdateLine(mousePoint);
		signalOutput.LinkInput(nullptr);
		return &signalOutput;
	}
	return nullptr;
}

void Input::Move(const D2D1_POINT_2F& mousePoint)
{
	centerPoint.x = mousePoint.x - mouseOffset.x;
	centerPoint.y = mousePoint.y - mouseOffset.y;
	signalOutput.Move(centerPoint);
}