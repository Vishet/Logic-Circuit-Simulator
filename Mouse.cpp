#include "Mouse.h"

Mouse::Mouse()
{
	POINT pt{};
	GetCursorPos(&pt);

	x = pt.x;
	y = pt.y;
}

void Mouse::OnLeftDown()
{
	if (leftButtonStatus == MouseStatus::UP)
		leftButtonStatus = MouseStatus::PRESSED;
	else
		leftButtonStatus = MouseStatus::DOWN;
}

void Mouse::OnLeftUp()
{
	if (leftButtonStatus == MouseStatus::DOWN)
		leftButtonStatus = MouseStatus::RELEASED;
	else
		leftButtonStatus = MouseStatus::UP;
}

void Mouse::OnRightDown()
{
	if (rightButtonStatus == MouseStatus::UP)
		rightButtonStatus = MouseStatus::PRESSED;
	else
		rightButtonStatus = MouseStatus::DOWN;
}

void Mouse::OnRightUp()
{
	if (rightButtonStatus == MouseStatus::DOWN)
		rightButtonStatus = MouseStatus::RELEASED;
	else
		rightButtonStatus = MouseStatus::UP;
}

void Mouse::OnMove(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Mouse::Update()
{
	if (leftButtonStatus == MouseStatus::PRESSED)
		leftButtonStatus = MouseStatus::DOWN;
	else if (leftButtonStatus == MouseStatus::RELEASED)
		leftButtonStatus = MouseStatus::UP;

	if (rightButtonStatus == MouseStatus::PRESSED)
		rightButtonStatus = MouseStatus::DOWN;
	else if (rightButtonStatus == MouseStatus::RELEASED)
		rightButtonStatus = MouseStatus::UP;
}

POINT Mouse::GetMousePosition() const
{
	return POINT{ x, y };
}