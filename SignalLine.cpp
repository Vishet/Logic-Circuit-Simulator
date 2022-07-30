#include "SignalLine.h"

SignalLine::SignalLine(const Graphics* pGraphics, const D2D1_POINT_2F& pointA, const D2D1_POINT_2F& pointB, const D2D1_COLOR_F& color, const D2D1_COLOR_F& activeColor, float strokeWidth) :
	pGraphics{ pGraphics },
	pointA{ pointA },
	pointB{ pointB },
	strokeWidth{ strokeWidth },
	activeColor{ activeColor },
	CircuitItem(color, CircuitItem::ItemType::SIGNAL_LINE)
{
}

SignalLine::~SignalLine()
{
	if (linkedSignalLine)
		delete linkedSignalLine;
}

void SignalLine::ChangePointB(const D2D1_POINT_2F& point)
{
	if (linkedSignalLine)
	{
		linkedSignalLine->ChangePointB(point);
		return;
	}
	if (!directionLocked)
	{
		pointB.x = point.x;
		pointB.y = point.y;
		return;
	}

	if (abs(point.x - pointA.x) >= abs(point.y - pointA.y))
	{
		pointB.x = point.x;
		pointB.y = pointA.y;
	}
	else
	{
		pointB.y = point.y;
		pointB.x = pointA.x;
	}		
}

void SignalLine::SetStatus(bool status) 
{ 
	this->status = status;
	if (linkedSignalLine)
		linkedSignalLine->SetStatus(status);
}

void SignalLine::SetLockDirection(bool lock)
{
	if (linkedSignalLine)
		linkedSignalLine->SetLockDirection(lock);
	else
		directionLocked = lock;
}

void SignalLine::CreateLinkLine()
{
	if (linkedSignalLine)
	{
		linkedSignalLine->CreateLinkLine();
		return;
	}

	linkedSignalLine = new SignalLine(pGraphics, pointB, pointB, bgColor, activeColor, strokeWidth);
	linkedSignalLine->SetStatus(status);
}

void SignalLine::Reset()
{
	pointB = pointA;
	delete linkedSignalLine;
	linkedSignalLine = nullptr;
}

void SignalLine::Draw() const
{
	if (linkedSignalLine)
		linkedSignalLine->Draw();

	if (pointA.x == pointB.x && pointA.y == pointB.y)
		return;

	if(status)
		pGraphics->DrawLine(pointA, pointB, activeColor, strokeWidth);
	else
		pGraphics->DrawLine(pointA, pointB, bgColor, strokeWidth);
}